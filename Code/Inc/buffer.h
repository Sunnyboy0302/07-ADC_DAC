//
// Created by Administrator on 2023/5/19.
//

#ifndef INC_06_TIMER_BUFFER_H
#define INC_06_TIMER_BUFFER_H

#include "stm32f4xx_hal.h"

#define MAX_BUFFER_SIZE 64 // max transmit/receive buffer size
#define MAX_DB_SIZE 10     // max data blocks size
#define MAX_RX_SIZE 8      // max single receive buffer size
#define MAX_TX_SIZE 16     // max single transmit buffer size

typedef struct {
  uint8_t *start;
  int size;
} DataBlocks_TypeDef;

typedef struct {
  // 所有数据块的缓存位置
  uint8_t data[MAX_BUFFER_SIZE];
  // 每一个数据块的起始位置和大小, 方便使用memcpy()函数
  DataBlocks_TypeDef blocks[MAX_DB_SIZE];
  int head, tail; // 数据块的 head & tail
  int cnt; // 当前总共接收了多少字节
} UART_Buffer_TypeDef;

extern UART_Buffer_TypeDef RX_BUF, TX_BUF;

void UART_Buffer_Init(UART_Buffer_TypeDef* buf);

int UART_Buffer_isEmpty(UART_Buffer_TypeDef* buf);

int UART_Buffer_isFull(UART_Buffer_TypeDef* buf);

void UART_Buffer_Push(UART_Buffer_TypeDef* buf, const uint8_t *data, int size);

DataBlocks_TypeDef* UART_Buffer_Pop(UART_Buffer_TypeDef* buf);

#endif //INC_06_TIMER_BUFFER_H
