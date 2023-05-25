//
// Created by Administrator on 2023/5/25.
//

#ifndef INC_06_TIMER_UART_H
#define INC_06_TIMER_UART_H

#include "stm32f4xx_hal.h"
#include "buffer.h"

HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, UART_Buffer_TypeDef *buf);

#endif //INC_06_TIMER_UART_H
