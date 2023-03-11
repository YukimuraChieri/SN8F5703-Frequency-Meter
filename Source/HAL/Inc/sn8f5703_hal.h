#ifndef __SN8F5703_HAL_H
#define __SN8F5703_HAL_H

#include "SN8F5703.h"

/* HAL状态枚举 */
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

void SystemClock_Init(void);    /* 初始化系统时钟 */
void HAL_Delay(uint16_t Delay); /* 毫秒级延时函数 */


#endif
