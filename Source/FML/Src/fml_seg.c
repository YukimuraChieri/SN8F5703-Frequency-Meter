#include "fml_seg.h"

/* 数码管段码0~9, L, 空 */
code uint8_t SEG_CODE[12] = { 0xEE, 0x0A, 0xE9, 0xAB, 0x0F, 0xA7, 0xE7, 0x8A, 0xEF, 0xAF, 0x64, 0x00 };
/* 数码管位选地址 */
code uint8_t DIG_CODE[4] = { 0xC4, 0xC2, 0xC0, 0xC6};

/* 初始化数码管 */
void FML_SEG_Init(void)
{
	uint8_t i;
	
	HDL_TM1628_Init();				/* 初始化TM1628 */
	HDL_TM1628_SendCMD(0x03);	/* 7位10段显示模式 */
	HDL_TM1628_SendCMD(0x40);	/* 地址自增模式 */
	HDL_TM1628_SendCMD(0xC0);	/* 设置起始地址 */
	for (i = 0; i < 8; i++)		/* 清空数码管显示 */	
	{
		HDL_TM1628_WriteByte(0x00);
	}
	HDL_TM1628_SendCMD(0x44);	/* 地址固定模式 */	
	HDL_TM1628_SendCMD(0x8F);	/* 开启显示 */
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS引脚置高 */
}

/* 数码管显示函数 */
void FML_SEG_Display(uint8_t dig, uint8_t seg)
{
	HDL_TM1628_SendCMD(DIG_CODE[dig]);		/* TM1628写入地址 */
	HDL_TM1628_WriteByte(SEG_CODE[seg]);	/* TM1628写入数据 */	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS引脚置高 */
}

/* 数码管显示数字 */
void FML_SEG_ShowNum(uint16_t num)
{
	if ( num < 10000 )	/* 显示数字在范围内 */
	{
		FML_SEG_Display( 0, (num/1000) );
		FML_SEG_Display( 1, (num/100)%10 );
		FML_SEG_Display( 2, (num/10)%10 );
		FML_SEG_Display( 3, (num%10) );
	}
	else								/* 显示超范围 */
	{
		FML_SEG_Display( 0, 11 );		/* 第1位不显示 */
		FML_SEG_Display( 1, 0 );		/* 第2位显示0 */
		FML_SEG_Display( 2, 10 );		/* 第3位显示L */
		FML_SEG_Display( 3, 11 );		/* 第4位不显示 */
	}
}

