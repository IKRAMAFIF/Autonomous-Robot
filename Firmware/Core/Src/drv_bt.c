#include "drv_bt.h"
#include <string.h>

/* UART Bluetooth */
extern UART_HandleTypeDef huart3;

/* ===== Variables ===== */
uint8_t  BT_rxByte;
char     BT_cmd[BT_RX_BUF_SIZE];
static uint16_t BT_rxIndex = 0;
uint8_t  BT_cmdReady = 0;

/* =========================================================
 *                 INITIALISATION BT
 * ========================================================= */
void BT_Init(void)
{
    BT_rxIndex = 0;
    BT_cmdReady = 0;
    memset(BT_cmd, 0, BT_RX_BUF_SIZE);

    HAL_UART_Receive_IT(&huart3, &BT_rxByte, 1);
}

/* =========================================================
 *                 ENVOI STRING
 * ========================================================= */
void BT_SendString(char *s)
{
    HAL_UART_Transmit(&huart3, (uint8_t*)s, strlen(s), HAL_MAX_DELAY);
}

/* =========================================================
 *            CALLBACK RECEPTION UART (1 octet)
 * ========================================================= */
void BT_UART_RxCpltCallback(uint8_t c)
{
    if (BT_cmdReady == 0)
    {
        if (c == '\n' || c == '\r')
        {
            BT_cmd[BT_rxIndex] = '\0';
            BT_cmdReady = 1;
            BT_rxIndex = 0;
        }
        else
        {
            if (BT_rxIndex < BT_RX_BUF_SIZE - 1)
            {
                BT_cmd[BT_rxIndex++] = c;
            }
            else
            {
                // overflow → reset buffer
                BT_rxIndex = 0;
            }
        }
    }

    HAL_UART_Receive_IT(&huart3, &BT_rxByte, 1);
}
