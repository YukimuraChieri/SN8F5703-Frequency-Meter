#include "dio.h"

/* 初始化函数 */
void HAL_GPIO_Init(uint8_t GPIOx, GPIO_InitTypeDef* GPIO_Init)
{
	if (GPIOx == P0)	/* P0端口初始化 */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P0M &= ~GPIO_Init->Pin;	/* 输入模式 */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P0M |= GPIO_Init->Pin;	/* 输出模式 */
				P0OC &= ~GPIO_Init->Pin;/* 禁用开漏 */
			}break;
			
			case GPIO_MODE_OUTPUT_OC: {
				P0M |= GPIO_Init->Pin;	/* 输出模式 */
				P0OC |= GPIO_Init->Pin;	/* 使能开漏 */
			}break;
		}
		
		if (GPIO_Init->Pull)
		{
			P0UR |= GPIO_Init->Pin;		/* 使能上拉 */
		}
		else
		{
			P0UR &= ~GPIO_Init->Pin;	/* 禁用上拉 */
		}
	}
	else if (GPIOx == P1)	/* P1端口初始化 */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P1M &= ~GPIO_Init->Pin;	/* 输入模式 */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P1M |= GPIO_Init->Pin;	/* 输出模式 */
			}break;
			
			default: break;
		}
		
		if (GPIO_Init->Pull)
		{
			P1UR |= GPIO_Init->Pin;		/* 使能上拉 */
		}
		else
		{
			P1UR &= ~GPIO_Init->Pin;	/* 禁用上拉 */
		}
	}
	else if (GPIOx == P2)	/* P2端口初始化 */
	{
		if (GPIO_Init->Pin <= GPIO_Pin_5)
		{
			switch(GPIO_Init->Mode)
			{
				case GPIO_MODE_INPUT: {
					P1M &= ~GPIO_Init->Pin;	/* 输入模式 */
				}break;
				
				case GPIO_MODE_OUTPUT_PP: {
					P1M |= GPIO_Init->Pin;	/* 输出模式 */
				}break;
				
				default: break;
			}
		
			if (GPIO_Init->Pull)
			{
				P1UR |= GPIO_Init->Pin;		/* 使能上拉 */
			}
			else
			{
				P1UR &= ~GPIO_Init->Pin;	/* 禁用上拉 */
			}
		}
	}
}

