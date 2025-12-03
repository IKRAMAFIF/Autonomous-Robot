#ifndef BORDER_SENSORS_H
#define BORDER_SENSORS_H

#include "stm32g4xx_hal.h"

typedef struct
{
    uint8_t B1;   // FRONT  (PA0)
    uint8_t B2;   // LEFT   (PA1)
    uint8_t B3;   // RIGHT  (PA4)
    uint8_t B4;   // BACK   (PA5)
} BorderStatus_t;

typedef enum {
    BORDER_NONE    = 0,
    BORDER_FRONT   = 1,
    BORDER_LEFT    = 2,
    BORDER_RIGHT   = 3,
    BORDER_BACK    = 4
} BorderDirection_t;

uint8_t BorderSensor_Read(GPIO_TypeDef* PORT, uint16_t PIN);
BorderStatus_t BorderSensors_ReadAll(void);
BorderDirection_t BorderSensors_GetDirection(void);

#endif
