#ifndef __SN8F5703_HAL_PWM_H
#define __SN8F5703_HAL_PWM_H

#include "SN8F5703.h"

/* PWMͨ������ */
#define PWM_CHANNEL_10  ((uint8_t)0x01)
#define PWM_CHANNEL_11  ((uint8_t)0x02)
#define PWM_CHANNEL_12  ((uint8_t)0x04)
#define PWM_CHANNEL_20  ((uint8_t)0x10)
#define PWM_CHANNEL_21  ((uint8_t)0x20)
#define PWM_CHANNEL_22  ((uint8_t)0x40)

/* PWMʱ�ӷ�Ƶ���� */
#define PWM_CLKDIV_128  ((uint8_t)0x00)
#define PWM_CLKDIV_64   ((uint8_t)0x10)
#define PWM_CLKDIV_32   ((uint8_t)0x20)
#define PWM_CLKDIV_16   ((uint8_t)0x30)
#define PWM_CLKDIV_8    ((uint8_t)0x40)
#define PWM_CLKDIV_4    ((uint8_t)0x50)
#define PWM_CLKDIV_2    ((uint8_t)0x60)
#define PWM_CLKDIV_1    ((uint8_t)0x70)

/* PWM������Զ��� */
#define PWM1X_OCPolarity_HIGH   ((uint8_t)0x04)
#define PWM1X_OCPolarity_LOW    ((uint8_t)0xFB)
#define PWM2X_OCPolarity_HIGH   ((uint8_t)0x08)
#define PWM2X_OCPolarity_LOW    ((uint8_t)0xF7)

/* PWM��ʼ���ṹ�嶨�� */
typedef struct
{
	uint16_t Period;        /* ���� */
	uint16_t Pulse;					/* PWMռ�ձ� */
	uint8_t ClockDivision;  /* PWMʱ�ӷ�Ƶ */
	uint8_t OCPolarity_1X;  /* PWM1X������� */
	uint8_t OCPolarity_2X;  /* PWM2X������� */
}PWM_InitTypeDef;

/* HAL��PWMģ���ຯ���궨��ӿ� */
#define __HAL_TIM_SET_COMPARE(__COMPARE__) PW1D = ((uint16_t)__COMPARE__)
#define __HAL_PWM_SET_PERIOD(__PERIOD__) PW1Y = ((uint16_t)__PERIOD__)

/* HAL��PWMģ��ӿں��� */
void HAL_PWM_Init(PWM_InitTypeDef* PWM_Init);
void HAL_PWM_Start(uint8_t Channel);
void HAL_PWM_Stop(uint8_t Channel);


#endif

