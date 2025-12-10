#pragma once
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "drv_bt.h"
#include "border_sensors.h"
#include "ADXL343_driver.h"
#include "ydlidar.h"
#include "MoteurPWM.h"

typedef enum {
    ROBOT_STOP = 0,
    ROBOT_MODE_CHAT,
    ROBOT_MODE_SOURIS
} RobotMode_t;

extern RobotMode_t robot_mode;
extern SemaphoreHandle_t mutexSensors;

void RobotModeTask(void *argument);
void BorderTask(void *argument);
void ShockTask(void *argument);
void BluetoothTask(void *argument);
void LidarTask(void *argument);
void MotorTask(void *argument);
