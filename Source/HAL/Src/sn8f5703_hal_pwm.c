#include "sn8f5703_hal_pwm.h"

void HAL_PWM_Init(PWM_InitTypeDef* PWM_Init)
{
	/* PWM时钟分频设置 */
	PW1M &= ~(0x70);
	PW1M |= PWM_Init->ClockDivision;
	/* PWM周期设置 */	
	PW1YH = (uint8_t)(PWM_Init->Period >> 8);
	PW1YL = (uint8_t)(PWM_Init->Period & (uint16_t)0x00FF);
	/* PWM占空比设置 */
	PW1DH = (uint8_t)(PWM_Init->Pulse >> 8);
	PW1DL = (uint8_t)(PWM_Init->Pulse & (uint16_t)0x00FF);
	
	/* PWM1X极性设置 */
	switch (PWM_Init->OCPolarity_1X)
	{
		case PWM1X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_1X; break;
		case PWM1X_OCPolarity_LOW: PW1M &= PWM_Init->OCPolarity_1X; break;
	}
	/* PWM2X极性设置 */
	switch (PWM_Init->OCPolarity_2X)
	{
		case PWM2X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_2X; break;
		case PWM2X_OCPolarity_LOW: PW1M &= PWM_Init->OCPolarity_2X; break;
	}
}

void HAL_PWM_Start(uint8_t Channel)
{
	PW1M |= 0x80;       /* 使能PWM功能 */
	PW1CH |= Channel;   /* 开启PWM通道 */
}

void HAL_PWM_Stop(uint8_t Channel)
{
	PW1M &= ~0x80;      /* 禁止PWM功能 */
	PW1CH &= ~Channel;  /* 关闭PWM通道 */
}

void HAL_PWM_Set_Compare(uint16_t Compare)
{
	/* PWM占空比设置 */
	PW1DH = (uint8_t)(Compare >> 8);
	PW1DL = (uint8_t)(Compare & (uint16_t)0x00FF);
}

void HAL_PWM_Set_Period(uint16_t Period)
{
	/* PWM周期设置 */	
	PW1YH = (uint8_t)(Period >> 8);
	PW1YL = (uint8_t)(Period & (uint16_t)0x00FF);
}



