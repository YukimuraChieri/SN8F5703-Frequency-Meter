#include "sn8f5703_hal_gpio.h"

/* ��ʼ������ */
void HAL_GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_InitTypeDef* GPIO_Init)
{
	if (GPIOx == Port0)	/* P0�˿ڳ�ʼ�� */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P0M &= ~GPIO_Init->Pin;	/* ����ģʽ */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P0M |= GPIO_Init->Pin;	/* ���ģʽ */
				if (GPIO_Init->Pin <= GPIO_Pin_2)
				{
					P0OC &= GPIO_Init->Pin;			/* ���ÿ�© */
				}
				else if (GPIO_Init->Pin <= GPIO_Pin_6)
				{
					P0OC &= ~(GPIO_Init->Pin << 2);	/* ���ÿ�© */
				}
			}break;
			
			case GPIO_MODE_OUTPUT_OC: {
				P0M |= GPIO_Init->Pin;	/* ���ģʽ */
				if (GPIO_Init->Pin <= GPIO_Pin_2)
				{
					P0OC |= GPIO_Init->Pin;			/* ʹ�ܿ�© */
				}
				else if (GPIO_Init->Pin <= GPIO_Pin_6)
				{
					P0OC |= (GPIO_Init->Pin << 2);	/* ʹ�ܿ�© */
				}
				
			}break;
		}
		
		if (GPIO_Init->Pull)
		{
			P0UR |= GPIO_Init->Pin;		/* ʹ������ */
		}
		else
		{
			P0UR &= ~GPIO_Init->Pin;	/* �������� */
		}
	}
	else if (GPIOx == Port1)	/* P1�˿ڳ�ʼ�� */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P1M &= ~GPIO_Init->Pin;	/* ����ģʽ */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P1M |= GPIO_Init->Pin;	/* ���ģʽ */
			}break;
			
			default: break;
		}
		
		if (GPIO_Init->Pull)
		{
			P1UR |= GPIO_Init->Pin;		/* ʹ������ */
		}
		else
		{
			P1UR &= ~GPIO_Init->Pin;	/* �������� */
		}
	}
	else if (GPIOx == Port2)	/* P2�˿ڳ�ʼ�� */
	{
		if (GPIO_Init->Pin <= GPIO_Pin_5)
		{
			switch(GPIO_Init->Mode)
			{
				case GPIO_MODE_INPUT: {
					P1M &= ~GPIO_Init->Pin;	/* ����ģʽ */
				}break;
				
				case GPIO_MODE_OUTPUT_PP: {
					P1M |= GPIO_Init->Pin;	/* ���ģʽ */
				}break;
				
				default: break;
			}
		
			if (GPIO_Init->Pull)
			{
				P1UR |= GPIO_Init->Pin;		/* ʹ������ */
			}
			else
			{
				P1UR &= ~GPIO_Init->Pin;	/* �������� */
			}
		}
	}
}

/* �������ú��� */
void HAL_GPIO_WritePin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin, uint8_t pinState)
{
	switch(GPIOx)	/* ѡ��GPIO�˿� */
	{
		case Port0: {	/* P0�˿� */
			if (1 == pinState)	/* ����Pin����� */
			{
				P0 |= GPIO_Pin;
			}
			else
			{
				P0 &= ~GPIO_Pin;
			}
		}break;

		case Port1: {	/* P1�˿� */
			if (1 == pinState)
			{
				P1 |= GPIO_Pin;
			}
			else
			{
				P1 &= ~GPIO_Pin;
			}
		}break;

		case Port2: {	/* P2�˿� */
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

/* ���Ŷ�ȡ���� */
uint8_t HAL_GPIO_ReadPin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin)
{
	uint8_t ret = 0;

	switch(GPIOx)	/* ѡ��GPIO�˿� */
	{
		case Port0: {	/* P0�˿� */
			ret = P0 & GPIO_Pin;	/* ͨ��λ�������ȡĳ��Pin�ŵĵ�ƽ */
		}break;

		case Port1: {	/* P1�˿� */
			ret = P1 & GPIO_Pin;
		}break;

		case Port2: {	/* P2�˿� */
			ret = P2 & GPIO_Pin;
		}break;
	}
	return ret;
}
