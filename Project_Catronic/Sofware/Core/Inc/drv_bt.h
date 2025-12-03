#ifndef DRV_BT_H
#define DRV_BT_H

#include "stm32g4xx_hal.h"
#include <string.h>

#define BT_RX_BUF_SIZE 100

extern UART_HandleTypeDef huart3;

extern uint8_t  BT_rxByte;
extern char     BT_rxBuffer[BT_RX_BUF_SIZE];
extern uint16_t BT_rxIndex;

void BT_Init(void);
void BT_SendString(char *s);
void BT_UART_RxCpltCallback(uint8_t c);

#endif
