//
// Created by Administrator on 2023/5/19.
//

#include "buffer.h"
#include "string.h"

UART_Buffer_TypeDef RX_BUF, TX_BUF;

void UART_Buffer_Init(UART_Buffer_TypeDef* buf)
{
  // buffer初始化
  buf->head = buf->tail = 0; // 均指向第一个数据块
  buf->cnt  = 0;
  buf->blocks[buf->tail].start = buf->data + buf->cnt;
}

int UART_Buffer_isEmpty(UART_Buffer_TypeDef* buf)
{
  return (buf->head == buf->tail);
}

int UART_Buffer_isFull(UART_Buffer_TypeDef* buf)
{
  return ((buf->tail+1) % MAX_DB_SIZE == buf->head);
}

void UART_Buffer_Push(UART_Buffer_TypeDef* buf, const uint8_t *data, int size)
{
  __disable_irq();
  buf->tail = (buf->tail + 1) % MAX_DB_SIZE;
  if(size >= MAX_BUFFER_SIZE - buf->cnt) // 当前要写入的字节数大于剩余空间, 缓存"回卷"
    buf->cnt = 0;
  buf->blocks[buf->tail].start = buf->data + buf->cnt;
  buf->blocks[buf->tail].size = size;
  buf->cnt += size;
  memcpy(buf->blocks[buf->tail].start, data, size);
  __enable_irq();
}

DataBlocks_TypeDef* UART_Buffer_Pop(UART_Buffer_TypeDef* buf)
{
  __disable_irq();
  buf->head = (buf->head + 1) % MAX_DB_SIZE;
  __enable_irq();
  return &buf->blocks[buf->head];
}
