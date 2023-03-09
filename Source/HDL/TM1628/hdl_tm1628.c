#include "hdl_tm1628.h"

/* 初始化TM1628 */
void HDL_TM1628_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TM1628 CS片选引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* 推挽输出 */
    GPIO_InitStructure.Pin = GPIO_Pin_0;            /* Pin0脚 */
    GPIO_InitStructure.Pull = 0;                    /* 禁用上拉 */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 CLK时钟引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* 推挽输出 */
    GPIO_InitStructure.Pin = GPIO_Pin_4;            /* Pin4脚 */
    GPIO_InitStructure.Pull = 0;                    /* 禁用上拉 */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 DIO数据引脚初始化 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* 推挽输出 */
    GPIO_InitStructure.Pin = GPIO_Pin_5;            /* Pin5脚 */
    GPIO_InitStructure.Pull = 0;                    /* 禁用上拉 */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* 初始化各引脚电平 */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS引脚置高 */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK引脚置高 */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_SET);     /* DIO引脚置高 */
}

/* TM1628写入1字节 */
void HDL_TM1628_WriteByte(uint8_t dat)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_RESET);   /* CLK引脚拉低 */

        if (dat & ((uint8_t)0x01))
        {
            HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_SET); /* DIO引脚置高 */
        }
        else
        {
            HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_RESET); /* DIO引脚拉低 */
        }
        dat >>= 1;

        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK引脚置高 */
    }
}

/* TM1628读取1字节 */
uint8_t HDL_TM1628_ReadByte(void)
{
    uint8_t i, dat = 0;

    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);	/* CS引脚拉低 */

    for (i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_RESET);   /* CLK引脚拉低 */
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK引脚置高 */
        if (GPIO_PIN_SET == HAL_GPIO_ReadPin(Port2, GPIO_Pin_5))	/* 读取DIO脚电平 */
        {
            dat |= ((uint8_t)0x01);
        }
        dat <<= 1;
    }

    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);		/* CS引脚置高 */

    return dat;
}

/* TM1628发送命令 */
void HDL_TM1628_SendCMD(uint8_t cmd)
{
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS引脚置高 */
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS引脚拉低 */
	
	HDL_TM1628_WriteByte(cmd);
}
