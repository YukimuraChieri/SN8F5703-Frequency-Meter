#ifndef __HDL_TM1628_H
#define __HDL_TM1628_H

#include "sn8f5703_hal_gpio.h"

void HDL_TM1628_Init(void);							/* ��ʼ��TM1628 */
void HDL_TM1628_WriteByte(uint8_t dat);	/* TM1628д��1�ֽ� */
uint8_t HDL_TM1628_ReadByte(void);			/* TM1628��ȡ1�ֽ� */

void HDL_TM1628_SendCMD(uint8_t cmd);		/* TM1628�������� */

#endif

