#ifndef __SN8F5703_HAL_PWM_H
#define __SN8F5703_HAL_PWM_H

#include "SN8F5703.h"

/* PWM通道定义 */
#define PWM_CHANNEL_10  ((uint8_t)0x01)
#define PWM_CHANNEL_11  ((uint8_t)0x02)
#define PWM_CHANNEL_12  ((uint8_t)0x04)
#define PWM_CHANNEL_20  ((uint8_t)0x10)
#define PWM_CHANNEL_21  ((uint8_t)0x20)
#define PWM_CHANNEL_22  ((uint8_t)0x40)

/* PWM时钟分频定义 */
#define PWM_CLKDIV_128  ((uint8_t)0x00)
#define PWM_CLKDIV_64   ((uint8_t)0x10)
#define PWM_CLKDIV_32   ((uint8_t)0x20)
#define PWM_CLKDIV_16   ((uint8_t)0x30)
#define PWM_CLKDIV_8    ((uint8_t)0x40)
#define PWM_CLKDIV_4    ((uint8_t)0x50)
#define PWM_CLKDIV_2    ((uint8_t)0x60)
#define PWM_CLKDIV_1    ((uint8_t)0x70)

/* PWM输出极性定义 */
#define PWM1X_OCPolarity_HIGH   ((uint8_t)0x04)
#define PWM1X_OCPolarity_LOW    ((uint8_t)0xFB)
#define PWM2X_OCPolarity_HIGH   ((uint8_t)0x08)
#define PWM2X_OCPolarity_LOW    ((uint8_t)0xF7)

/* PWM初始化结构体定义 */
typedef struct
{
	uint16_t Period;        /* 周期 */
	uint16_t Pulse;					/* PWM占空比 */
	uint8_t ClockDivision;  /* PWM时钟分频 */
	uint8_t OCPolarity_1X;  /* PWM1X输出极性 */
	uint8_t OCPolarity_2X;  /* PWM2X输出极性 */
}PWM_InitTypeDef;

/* HAL层PWM模块类函数宏定义接口 */
#define __HAL_TIM_SET_COMPARE(__COMPARE__) PW1D = ((uint16_t)__COMPARE__)
#define __HAL_PWM_SET_PERIOD(__PERIOD__) PW1Y = ((uint16_t)__PERIOD__)

/* HAL层PWM模块接口函数 */
void HAL_PWM_Init(PWM_InitTypeDef* PWM_Init);
void HAL_PWM_Start(uint8_t Channel);
void HAL_PWM_Stop(uint8_t Channel);


#endif

