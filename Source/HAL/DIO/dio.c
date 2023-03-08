#include "dio.h"

/* ��ʼ������ */
void HAL_GPIO_Init(uint8_t GPIOx, GPIO_InitTypeDef* GPIO_Init)
{
	if (GPIOx == P0)	/* P0�˿ڳ�ʼ�� */
	{
		switch(GPIO_Init->Mode)
		{
			case GPIO_MODE_INPUT: {
				P0M &= ~GPIO_Init->Pin;	/* ����ģʽ */
			}break;
			
			case GPIO_MODE_OUTPUT_PP: {
				P0M |= GPIO_Init->Pin;	/* ���ģʽ */
				P0OC &= ~GPIO_Init->Pin;/* ���ÿ�© */
			}break;
			
			case GPIO_MODE_OUTPUT_OC: {
				P0M |= GPIO_Init->Pin;	/* ���ģʽ */
				P0OC |= GPIO_Init->Pin;	/* ʹ�ܿ�© */
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
	else if (GPIOx == P1)	/* P1�˿ڳ�ʼ�� */
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
	else if (GPIOx == P2)	/* P2�˿ڳ�ʼ�� */
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

