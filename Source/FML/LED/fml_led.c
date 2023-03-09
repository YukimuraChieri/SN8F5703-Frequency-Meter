#include "fml_led.h"

/* ��ʼ��LED */
void FML_LED_Init(void)
{
	HDL_TM1628_Init();				/* ��ʼ��TM1628 */
	
	HDL_TM1628_SendCMD(0x03);	/* 7λ10����ʾģʽ */
	
	HDL_TM1628_SendCMD(0x44);	/* ��ַ�̶�ģʽ */
	
	HDL_TM1628_SendCMD(LED_ADDR);	/* ����LED��ʾ��ַ */
	
	HDL_TM1628_WriteByte(0x00);	/* ���LED��ʾ */
	
	HDL_TM1628_SendCMD(0x8F);	/* ������ʾ */
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS�����ø� */
}

/* LED��ʾ */
void FML_LED_Display(uint8_t ucled)
{
	HDL_TM1628_SendCMD(LED_ADDR);	/* ����LED��ʾ��ַ */
	
	HDL_TM1628_WriteByte(ucled);	/* ����LED��ʾ���� */
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS�����ø� */
}

