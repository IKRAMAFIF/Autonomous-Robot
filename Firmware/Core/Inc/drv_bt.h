#ifndef INC_DRV_BT_H_
#define INC_DRV_BT_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>

#define BT_RX_BUF_SIZE 64

/* ===== Variables globales Bluetooth ===== */
extern uint8_t  BT_rxByte;
extern char     BT_cmd[BT_RX_BUF_SIZE];
extern uint8_t  BT_cmdReady;

/* ===== Fonctions ===== */
void BT_Init(void);
void BT_SendString(char *s);
void BT_UART_RxCpltCallback(uint8_t c);

#endif /* INC_DRV_BT_H_ */
