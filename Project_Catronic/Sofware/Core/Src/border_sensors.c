#include "border_sensors.h"
#include "main.h"


uint8_t BorderSensor_Read(GPIO_TypeDef* PORT, uint16_t PIN)
{
    return (HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_SET);
}

BorderDirection_t BorderSensors_GetDirection(void)
{
    uint8_t front  = BorderSensor_Read(GPIOA, GPIO_PIN_0); // PA0
    uint8_t left   = BorderSensor_Read(GPIOA, GPIO_PIN_1); // PA1
    uint8_t right  = BorderSensor_Read(GPIOA, GPIO_PIN_4); // PA4
    uint8_t back   = BorderSensor_Read(GPIOA, GPIO_PIN_5); // PA5

    if (front)  return BORDER_FRONT;
    if (left)   return BORDER_LEFT;
    if (right)  return BORDER_RIGHT;
    if (back)   return BORDER_BACK;

    return BORDER_NONE;
}
