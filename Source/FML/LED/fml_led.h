#ifndef __FML_LED_H
#define __FML_LED_H

#include "hdl_tm1628.h"

/* LED显示地址 */
#define LED_ADDR ((uint8_t)0xC8)

/* LED对应输出 */
#define LED1	((uint8_t)0x80)
#define LED2	((uint8_t)0x04)
#define LED3	((uint8_t)0x08)
#define LED4	((uint8_t)0x40)
#define LED5	((uint8_t)0x01)
#define LED6	((uint8_t)0x02)
#define LED7	((uint8_t)0x10)
#define LED8	((uint8_t)0x20)

void FML_LED_Init(void);	/* 初始化LED */
void FML_LED_Display(uint8_t ucled);	/* LED显示 */

#endif

