#include "fml_key.h"

uint8_t key_buf[5] = {0};

/* 初始化按键 */
void FML_KEY_Init(void)
{
	HDL_TM1628_Init();  /* 初始化TM1628 */
}

/* 按键扫描 */
uint8_t FML_KEY_Scan(void)
{
	uint8_t ret = 0, i;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	HDL_TM1628_SendCMD(0x42);	/* TM1628读键盘命令 */
	
	/* TM1628 DIO数据引脚设置输入 */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;  /* 输入 */
	GPIO_InitStructure.Pin = GPIO_Pin_5;				/* Pin5脚 */
	GPIO_InitStructure.Pull = GPIO_NOPULL;			/* 禁用上拉 */
	HAL_GPIO_Init(Port2, &GPIO_InitStructure);
	
	for (i = 0; i < 5; i++)
	{
		key_buf[i] = HDL_TM1628_ReadByte();	/* TM1628读取数据 */	
	}
	
	/* TM1628 DIO数据引脚初始化 */
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* 推挽输出 */
	GPIO_InitStructure.Pin = GPIO_Pin_5;            /* Pin5脚 */
	GPIO_InitStructure.Pull = GPIO_NOPULL;          /* 禁用上拉 */
	HAL_GPIO_Init(Port2, &GPIO_InitStructure);
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS引脚置高 */
	
	if (key_buf[1] & 0x08)	/* 检测按键1 */
	{
		ret |= KEY1;
	}
	else if (key_buf[3] & 0x08)	/* 检测按键2 */
	{
		ret |= KEY2;
	}
	else if (key_buf[3] & 0x01)	/* 检测按键3 */
	{
		ret |= KEY3;
	}
	else if (key_buf[1] & 0x01)	/* 检测按键4 */
	{
		ret |= KEY4;
	}
	
	return ret;
}
