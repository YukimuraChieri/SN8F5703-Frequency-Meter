#ifndef __SN8F5703_HAL_DELAY_H
#define __SN8F5703_HAL_DELAY_H

#include "SN8F5703.h"

void SystemClock_Init(void);    /* 初始化系统时钟 */
void HAL_Delay(uint16_t Delay); /* 毫秒级延时函数 */


#endif
