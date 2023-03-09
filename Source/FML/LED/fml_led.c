#include "fml_led.h"

/* 初始化LED */
void FML_LED_Init(void)
{
	HDL_TM1628_Init();				/* 初始化TM1628 */
	
	HDL_TM1628_SendCMD(0x03);	/* 7位10段显示模式 */
	
	HDL_TM1628_SendCMD(0x44);	/* 地址固定模式 */
	
	HDL_TM1628_SendCMD(LED_ADDR);	/* 设置LED显示地址 */
	
	HDL_TM1628_WriteByte(0x00);	/* 清空LED显示 */
	
	HDL_TM1628_SendCMD(0x8F);	/* 开启显示 */
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS引脚置高 */
}

/* LED显示 */
void FML_LED_Display(uint8_t ucled)
{
	HDL_TM1628_SendCMD(LED_ADDR);	/* 设置LED显示地址 */
	
	HDL_TM1628_WriteByte(ucled);	/* 设置LED显示数据 */
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS引脚置高 */
}

