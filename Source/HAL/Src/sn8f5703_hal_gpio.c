#include "sn8f5703_hal_gpio.h"

/* 初始化函数 */
void HAL_GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_InitTypeDef* GPIO_Init)
{
	if (GPIOx == Port0)	/* P0端口初始化 */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P0M &= ~GPIO_Init->Pin;	/* 输入模式 */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P0M |= GPIO_Init->Pin;	/* 输出模式 */
				if (GPIO_Init->Pin <= GPIO_Pin_2)
				{
					P0OC &= GPIO_Init->Pin;			/* 禁用开漏 */
				}
				else if (GPIO_Init->Pin <= GPIO_Pin_6)
				{
					P0OC &= ~(GPIO_Init->Pin << 2);	/* 禁用开漏 */
				}
			}break;
			
			case GPIO_MODE_OUTPUT_OC: {
				P0M |= GPIO_Init->Pin;	/* 输出模式 */
				if (GPIO_Init->Pin <= GPIO_Pin_2)
				{
					P0OC |= GPIO_Init->Pin;			/* 使能开漏 */
				}
				else if ((GPIO_Init->Pin >= GPIO_Pin_4) && (GPIO_Init->Pin <= GPIO_Pin_6))
				{
					P0OC |= (GPIO_Init->Pin << 2);	/* 使能开漏 */
				}
				
			}break;
		}
		
		if (GPIO_PULLUP == GPIO_Init->Pull)
		{
			P0UR |= GPIO_Init->Pin;		/* 使能上拉 */
		}
		else
		{
			P0UR &= ~GPIO_Init->Pin;	/* 禁用上拉 */
		}
	}
	else if (GPIOx == Port1)	/* P1端口初始化 */
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
	else if (GPIOx == Port2)	/* P2端口初始化 */
	{
		if (GPIO_Init->Pin <= GPIO_Pin_5)
		{
			switch(GPIO_Init->Mode)
			{
				case GPIO_MODE_INPUT: {
					P2M &= ~GPIO_Init->Pin;	/* 输入模式 */
				}break;
				
				case GPIO_MODE_OUTPUT_PP: {
					P2M |= GPIO_Init->Pin;	/* 输出模式 */
				}break;
				
				default: break;
			}
		
			if (GPIO_Init->Pull)
			{
				P2UR |= GPIO_Init->Pin;		/* 使能上拉 */
			}
			else
			{
				P2UR &= ~GPIO_Init->Pin;	/* 禁用上拉 */
			}
		}
	}
}

/* 引脚设置函数 */
void HAL_GPIO_WritePin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin, uint8_t pinState)
{
	switch(GPIOx)	/* 选择GPIO端口 */
	{
		case Port0: {	/* P0端口 */
			if (1 == pinState)	/* 设置Pin脚输出 */
			{
				P0 |= GPIO_Pin;
			}
			else
			{
				P0 &= ~GPIO_Pin;
			}
		}break;

		case Port1: {	/* P1端口 */
			if (1 == pinState)
			{
				P1 |= GPIO_Pin;
			}
			else
			{
				P1 &= ~GPIO_Pin;
			}
		}break;

		case Port2: {	/* P2端口 */
			if (1 == pinState)
			{
				P2 |= GPIO_Pin;
			}
			else
			{
				P2 &= ~GPIO_Pin;
			}
		}break;
	}
}

/* 引脚读取函数 */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin)
{
	GPIO_PinState bitstatus = GPIO_PIN_RESET;

	switch(GPIOx)	/* 选择GPIO端口 */
	{
		case Port0: {	/* P0端口 */
			bitstatus = (P0 & GPIO_Pin)?GPIO_PIN_SET:GPIO_PIN_RESET;	/* 通过位与操作读取某个Pin脚的电平 */
		}break;

		case Port1: {	/* P1端口 */
			bitstatus = (P1 & GPIO_Pin)?GPIO_PIN_SET:GPIO_PIN_RESET;
		}break;

		case Port2: {	/* P2端口 */
			bitstatus = (P2 & GPIO_Pin)?GPIO_PIN_SET:GPIO_PIN_RESET;
		}break;
	}
	return bitstatus;
}

