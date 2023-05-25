//
// Created by Administrator on 2023/5/25.
//

#include "uart.h"

HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, UART_Buffer_TypeDef *buf)
{
  if (huart->gState == HAL_UART_STATE_READY)
    return HAL_UART_Transmit_IT(huart, pData, Size);
  else {// huart->gState == HAL_UART_STATE_BUSY
    UART_Buffer_Push(buf, pData, Size);
    return HAL_OK;
  }
}