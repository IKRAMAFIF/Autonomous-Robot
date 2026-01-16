#include "border_sensors.h"
#include "main.h"

uint8_t BorderSensor_Read(GPIO_TypeDef* PORT, uint16_t PIN)
{
    return (HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_RESET);
}

BorderDirection_t BorderSensors_GetDirection(void)
{
    // Lecture des 4 capteurs
    uint8_t avant_gauche     = BorderSensor_Read(GPIOA, GPIO_PIN_0); // PA0
    uint8_t avant_droite     = BorderSensor_Read(GPIOA, GPIO_PIN_1); // PA1
    uint8_t arriere_gauche   = BorderSensor_Read(GPIOA, GPIO_PIN_4); // PA4
    uint8_t arriere_droite   = BorderSensor_Read(GPIOA, GPIO_PIN_5); // PA5

    // Priorité : si plusieurs détectent, tu peux définir ta logique
    if (avant_gauche)   return BORDER_AVANT_GAUCHE;
    if (avant_droite)   return BORDER_AVANT_DROITE;
    if (arriere_gauche) return BORDER_ARRIERE_GAUCHE;
    if (arriere_droite) return BORDER_ARRIERE_DROITE;

    return BORDER_NONE;
}
