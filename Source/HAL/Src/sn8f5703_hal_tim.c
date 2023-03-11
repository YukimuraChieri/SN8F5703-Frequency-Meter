#include "sn8f5703_hal_tim.h"

void HAL_TIM2_Base_Init(TIM2_Base_InitTypeDef* htim)
{
	T2CON |= htim->Prescaler;	
	T2CON |= htim->AutoReloadPreload;
	T2CON |= htim->ClockSource;	
	/* TIM2计数器初值设置 */
	TH2 = (uint8_t)(htim->Period >> 8);
	TL2 = (uint8_t)(htim->Period & (uint16_t)0x00FF);
}

void HAL_TIM2_IC_Init(TIM2_IC_InitTypeDef* htim)
{
	T2CON |= htim->ICPolarity;	/* 极性选择 */
	
	if (htim->ICSelection & TIM2_IC_CHANNEL_0)
	{
		CCEN |= 0x01;
//		IEN1 |= 0X04;
	}
	if (htim->ICSelection & TIM2_IC_CHANNEL_1)
	{
		CCEN |= 0x04;
//		IEN1 |= 0X08;
	}
	if (htim->ICSelection & TIM2_IC_CHANNEL_2)
	{
		CCEN |= 0x10;
//		IEN1 |= 0X01;
	}
	if (htim->ICSelection & TIM2_IC_CHANNEL_3)
	{
		CCEN |= 0x40;
//		IEN1 |= 0X02;
	}
//	IEN0 |= 0XA0;
}

uint16_t HAL_TIM2_ReadCapturedValue(TIM2_IC_Channel Channel)
{
	uint16_t tmpreg;
	
	switch(Channel)
	{
		case TIM2_IC_CHANNEL_0: {
			tmpreg = ( ((uint16_t)CRCH) << 8 ) | ( (uint16_t)CRCL );
		}break;
		
		case TIM2_IC_CHANNEL_1: {
			tmpreg = ( ((uint16_t)CCH1) << 8 ) | ( (uint16_t)CCL1 );
		}break;
		
		case TIM2_IC_CHANNEL_2: {
			tmpreg = ( ((uint16_t)CCH2) << 8 ) | ( (uint16_t)CCL2 );
		}break;
		
		case TIM2_IC_CHANNEL_3: {
			tmpreg = ( ((uint16_t)CCH3) << 8 ) | ( (uint16_t)CCL3 );
		}break;
	}
	
	return tmpreg;
}

