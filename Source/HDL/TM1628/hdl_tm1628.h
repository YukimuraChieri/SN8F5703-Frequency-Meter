#ifndef __HDL_TM1628_H
#define __HDL_TM1628_H

#include "sn8f5703_hal_gpio.h"

void HDL_TM1628_Init(void);							/* 初始化TM1628 */
void HDL_TM1628_WriteByte(uint8_t dat);	/* TM1628写入1字节 */
uint8_t HDL_TM1628_ReadByte(void);			/* TM1628读取1字节 */

void HDL_TM1628_SendCMD(uint8_t cmd);		/* TM1628发送命令 */

#endif

