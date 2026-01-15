#include "robot_logic.h"
#include "border_sensors.h"
#include "drv_bt.h"
#include "ADXL343_driver.h"
#include "ydlidar.h"
#include "MoteurPWM.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string.h>
#include <stdio.h>
#include "main.h"

extern SemaphoreHandle_t mutexSensors;
extern I2C_HandleTypeDef hi2c1;
extern h_Robot hrob;


uint8_t shock_detected = 0;
uint8_t border_active = 0;
BorderDirection_t border_dir = BORDER_NONE;
RobotMode_t robot_mode = ROBOT_STOP;


void BorderTask(void *argument)
{
    printf("BorderTask STARTED\r\n");

    for (;;)
    {
BorderDirection_t d = BorderSensors_GetDirection();

        xSemaphoreTake(mutexSensors, portMAX_DELAY);
        border_dir = d;
        border_active = (d != BORDER_NONE);
        xSemaphoreGive(mutexSensors);

        if (d != BORDER_NONE)
            printf("BORDER DETECTED: %d\r\n", d);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}



void ShockTask(void *argument)
{
    HAL_StatusTypeDef ret;

    ret = ADXL343_Init(&hi2c1);
    ret = ADXL343_ConfigShock(&hi2c1, 0.3f, 50.0f);

    for (;;)
    {
        if (ADXL343_CheckShock(&hi2c1))
        {
        	printf("choc detecte\r\n");
            xSemaphoreTake(mutexSensors, portMAX_DELAY);
            if (robot_mode != ROBOT_STOP)
            {
                shock_detected = 1;

                if (robot_mode == ROBOT_MODE_CHAT)
                {
                    robot_mode = ROBOT_MODE_SOURIS;
                    BT_SendString("Mode auto -> SOURIS\r\n");
                    printf("Mode auto -> SOURIS\r\n");
                }
                else if (robot_mode == ROBOT_MODE_SOURIS)
                {
                    robot_mode = ROBOT_MODE_CHAT;
                    BT_SendString("Mode auto -> CHAT\r\n");
                    printf("Mode auto -> CHAT\r\n");
                }
            }

            xSemaphoreGive(mutexSensors);

            vTaskDelay(pdMS_TO_TICKS(300)); // anti-rebond
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


void BluetoothTask(void *argument)
{
    for (;;)
    {
        if (BT_cmdReady)
        {
            BT_cmdReady = 0;

            xSemaphoreTake(mutexSensors, portMAX_DELAY);

            if (strcmp(BT_cmd, "STOP") == 0)
            {
                robot_mode = ROBOT_STOP;
                BT_SendString("Robot STOP\r\n");
                printf("Robot STOP\r\n");
            }
            else if (strcmp(BT_cmd, "START") == 0)
            {
                robot_mode = ROBOT_MODE_CHAT;
                BT_SendString("Robot START -> CHAT\r\n");
                printf("Robot START -> CHAT\r\n");
            }
            else if (strcmp(BT_cmd, "CHAT") == 0)
            {
                robot_mode = ROBOT_MODE_CHAT;
                BT_SendString("Mode -> CHAT\r\n");
                printf("Mode -> CHAT\r\n");
            }
            else if (strcmp(BT_cmd, "SOURIS") == 0)
            {
                robot_mode = ROBOT_MODE_SOURIS;
                BT_SendString("Mode -> SOURIS\r\n");
                printf("Mode -> SOURIS\r\n");
            }
            else if (strcmp(BT_cmd, "STATUS") == 0)
            {
                if (robot_mode == ROBOT_MODE_CHAT)
                    BT_SendString("STATUS: CHAT\r\n");

                else if (robot_mode == ROBOT_MODE_SOURIS)
                    BT_SendString("STATUS: SOURIS\r\n");

                else
                    BT_SendString("STATUS: STOP\r\n");
            }
            else
            {
                BT_SendString("Commande inconnue\r\n");
            }

            memset(BT_cmd, 0, sizeof(BT_cmd));
            xSemaphoreGive(mutexSensors);
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}


void RobotModeTask(void *argument)
{extern Moteur_HandleTypeDef moteurD;
extern Moteur_HandleTypeDef moteurG;
    for (;;)
    {
        RobotMode_t mode;
        BorderDirection_t d;
        uint8_t b_active;

        xSemaphoreTake(mutexSensors, portMAX_DELAY);
        mode = robot_mode;
        d = border_dir;
        b_active = border_active;
        xSemaphoreGive(mutexSensors);

        if (mode == ROBOT_STOP)
        {
            Robot_Stop(&hrob);
        }
        else if (b_active)
        {
            // Sécurité bordure PRIORITAIRE
            if (d == BORDER_AVANT_GAUCHE || d == BORDER_AVANT_DROITE)
            {
                Robot_Recule(&hrob, 15);
                vTaskDelay(pdMS_TO_TICKS(600));
                Moteur_setSpeed(&moteurG, 5);
                vTaskDelay(pdMS_TO_TICKS(700));
                Robot_Stop(&hrob);
                vTaskDelay(pdMS_TO_TICKS(100));



            }
            else if (d == BORDER_ARRIERE_GAUCHE || d == BORDER_ARRIERE_DROITE)
            {
                Robot_Start(&hrob, 15);
                vTaskDelay(pdMS_TO_TICKS(600));
                Moteur_setSpeed(&moteurG, 5);
                vTaskDelay(pdMS_TO_TICKS(700));
                Robot_Stop(&hrob);
                vTaskDelay(pdMS_TO_TICKS(100));
            }
        }
        else if (mode == ROBOT_MODE_CHAT)
        {

            BT_SendString("avance chat\r\n");
            printf("avance chat\r\n");
       Robot_Start(&hrob, 17);

        }
        else if (mode == ROBOT_MODE_SOURIS)
        {

        	BT_SendString("avance souris\r\n");
        	printf("avance souris\r\n");
            Robot_Start(&hrob, 17);

        }

        vTaskDelay(pdMS_TO_TICKS(80));
    }
}
