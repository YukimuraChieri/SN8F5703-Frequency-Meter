#include "hdl_tm1628.h"

/* ��ʼ��TM1628 */
void HDL_TM1628_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TM1628 CSƬѡ���ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_0;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 CLKʱ�����ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_4;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 DIO�������ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_5;
    GPIO_InitStructure.Pull = 0;
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);
}

/* TM1628д��1�ֽ� */
void HDL_TM1628_WriteByte(uint8_t data)
{
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS�������� */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS�����ø� */
}

/* TM1628��ȡ1�ֽ� */
uint8_t HDL_TM1628_ReadByte(void)
{
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS�������� */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS�����ø� */
}
