#include "drv_bt.h"

uint8_t  BT_rxByte;
char     BT_rxBuffer[BT_RX_BUF_SIZE];
uint16_t BT_rxIndex = 0;

void BT_Init(void)
{
    HAL_UART_Receive_IT(&huart3, &BT_rxByte, 1);
}

void BT_SendString(char *s)
{
    HAL_UART_Transmit(&huart3, (uint8_t*)s, strlen(s), HAL_MAX_DELAY);
}

void BT_UART_RxCpltCallback(uint8_t c)
{
    BT_rxBuffer[BT_rxIndex++] = c;


    if (c == '\n' || c == '\r')
    {
        BT_rxBuffer[BT_rxIndex] = '\0';

        while (BT_rxIndex > 0 &&
               (BT_rxBuffer[BT_rxIndex-1] == '\r' || BT_rxBuffer[BT_rxIndex-1] == '\n'))
        {
            BT_rxBuffer[BT_rxIndex-1] = '\0';
            BT_rxIndex--;
        }

        // COMMANDES BLUETOOTH ici
        if (strcmp(BT_rxBuffer, "LED ON") == 0)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
        }
        else if (strcmp(BT_rxBuffer, "LED OFF") == 0)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
        }
        BT_rxIndex = 0;
    }

    HAL_UART_Receive_IT(&huart3, &BT_rxByte, 1);
}
