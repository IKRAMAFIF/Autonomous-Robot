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

extern SemaphoreHandle_t mutexSensors;
extern I2C_HandleTypeDef hi2c1;
extern h_Robot hrob;
uint8_t shock_detected = 0;
BorderDirection_t border_dir = BORDER_NONE;

void BorderTask(void *argument)
{
    for(;;)
    {
        BorderDirection_t d = BorderSensors_GetDirection();

        xSemaphoreTake(mutexSensors, portMAX_DELAY);
        border_dir = d;
        xSemaphoreGive(mutexSensors);

        switch(d)
        {
            case BORDER_AVANT_GAUCHE: // PA0 - capteur3
                printf("Avant Gauche detecte → Recule\r\n");
                Robot_Recule(&hrob, 40);
                vTaskDelay(pdMS_TO_TICKS(100));
                Robot_Stop(&hrob);
                break;

            case BORDER_AVANT_DROITE: // PA1 - capteur2
                printf("Avant Droite detecte → Recule\r\n");
                Robot_Recule(&hrob, 40);
                vTaskDelay(pdMS_TO_TICKS(100));
                Robot_Stop(&hrob);
                break;

            case BORDER_ARRIERE_GAUCHE: // PA4 - capteur4
                printf("Arrière Gauche detecte → Avance\r\n");
                Robot_Start(&hrob, 40);
                vTaskDelay(pdMS_TO_TICKS(100));
                Robot_Stop(&hrob);
                break;

            case BORDER_ARRIERE_DROITE: // PA5 - capteur1
                printf("Arrière Droite detecte → Avance\r\n");
                Robot_Start(&hrob, 40);
                vTaskDelay(pdMS_TO_TICKS(100));
                Robot_Stop(&hrob);
                break;

            case BORDER_NONE:
            default:
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}



void ShockTask(void *argument)
{
    printf("\r\n accelerometre (FreeRTOS) \r\n");

    HAL_StatusTypeDef ret;

    ret = ADXL343_Init(&hi2c1);
    if (ret != HAL_OK) {
        printf("ADXL343_Init ERROR !\r\n");
    } else {
        printf("ADXL343_Init OK\r\n");
    }

    ret = ADXL343_ConfigShock(&hi2c1, 0.3f, 50.0f);
    if (ret != HAL_OK) {
        printf("ADXL343_ConfigShock ERROR !\r\n");
    } else {
        printf("ADXL343_ConfigShock OK\r\n");
    }


    //LIRE CHOC + LED
    for(;;)
    {
        if (ADXL343_CheckShock(&hi2c1) == 1)
        {
            printf(" CHOC détecté !\r\n");

            xSemaphoreTake(mutexSensors, portMAX_DELAY);
            shock_detected = 1;
            xSemaphoreGive(mutexSensors);

            HAL_GPIO_WritePin(LED_ST1_GPIO_Port, LED_ST1_Pin, GPIO_PIN_SET);
            vTaskDelay(pdMS_TO_TICKS(200));
            HAL_GPIO_WritePin(LED_ST1_GPIO_Port, LED_ST1_Pin, GPIO_PIN_RESET);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}





