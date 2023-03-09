#include "hdl_tm1628.h"

/* 初始化TM1628 */
void HDL_TM1628_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TM1628 CS片选引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_0;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 CLK时钟引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_4;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 DIO数据引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_5;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);
}

/* TM1628写入1字节 */
void HDL_TM1628_WriteByte(uint8_t data)
{
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS引脚拉低 */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS引脚置高 */
}

/* TM1628读取1字节 */
uint8_t HDL_TM1628_ReadByte(void)
{
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS引脚拉低 */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS引脚置高 */
}
