#include "fml_seg.h"

/* ����ܶ���0~9, L, �� */
code uint8_t SEG_CODE[12] = { 0xEE, 0x0A, 0xE9, 0xAB, 0x0F, 0xA7, 0xE7, 0x8A, 0xEF, 0xAF, 0x64, 0x00 };
/* �����λѡ��ַ */
code uint8_t DIG_CODE[4] = { 0xC4, 0xC2, 0xC0, 0xC6};

/* ��ʼ������� */
void FML_SEG_Init(void)
{
	uint8_t i;
	
	HDL_TM1628_Init();				/* ��ʼ��TM1628 */
	HDL_TM1628_SendCMD(0x03);	/* 7λ10����ʾģʽ */
	HDL_TM1628_SendCMD(0x40);	/* ��ַ����ģʽ */
	HDL_TM1628_SendCMD(0xC0);	/* ������ʼ��ַ */
	for (i = 0; i < 8; i++)		/* ����������ʾ */	
	{
		HDL_TM1628_WriteByte(0x00);
	}
	HDL_TM1628_SendCMD(0x44);	/* ��ַ�̶�ģʽ */	
	HDL_TM1628_SendCMD(0x8F);	/* ������ʾ */
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS�����ø� */
}

/* �������ʾ���� */
void FML_SEG_Display(uint8_t dig, uint8_t seg)
{
	HDL_TM1628_SendCMD(DIG_CODE[dig]);		/* TM1628д���ַ */
	HDL_TM1628_WriteByte(SEG_CODE[seg]);	/* TM1628д������ */	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS�����ø� */
}

/* �������ʾ���� */
void FML_SEG_ShowNum(uint16_t num)
{
	if ( num < 10000 )	/* ��ʾ�����ڷ�Χ�� */
	{
		FML_SEG_Display( 0, (num/1000) );
		FML_SEG_Display( 1, (num/100)%10 );
		FML_SEG_Display( 2, (num/10)%10 );
		FML_SEG_Display( 3, (num%10) );
	}
	else								/* ��ʾ����Χ */
	{
		FML_SEG_Display( 0, 11 );		/* ��1λ����ʾ */
		FML_SEG_Display( 1, 0 );		/* ��2λ��ʾ0 */
		FML_SEG_Display( 2, 10 );		/* ��3λ��ʾL */
		FML_SEG_Display( 3, 11 );		/* ��4λ����ʾ */
	}
}

