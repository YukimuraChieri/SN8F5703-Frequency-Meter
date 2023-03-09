#include "hdl_tm1628.h"

/* ��ʼ��TM1628 */
void HDL_TM1628_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TM1628 CSƬѡ���ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* ������� */
    GPIO_InitStructure.Pin = GPIO_Pin_0;            /* Pin0�� */
    GPIO_InitStructure.Pull = 0;                    /* �������� */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 CLKʱ�����ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* ������� */
    GPIO_InitStructure.Pin = GPIO_Pin_4;            /* Pin4�� */
    GPIO_InitStructure.Pull = 0;                    /* �������� */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* TM1628 DIO�������ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* ������� */
    GPIO_InitStructure.Pin = GPIO_Pin_5;            /* Pin5�� */
    GPIO_InitStructure.Pull = 0;                    /* �������� */
    HAL_GPIO_Init(Port2, &GPIO_InitStructure);

    /* ��ʼ�������ŵ�ƽ */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS�����ø� */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK�����ø� */
    HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_SET);     /* DIO�����ø� */
}

/* TM1628д��1�ֽ� */
void HDL_TM1628_WriteByte(uint8_t dat)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_RESET);   /* CLK�������� */

        if (dat & ((uint8_t)0x01))
        {
            HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_SET); /* DIO�����ø� */
        }
        else
        {
            HAL_GPIO_WritePin(Port2, GPIO_Pin_5, GPIO_PIN_RESET); /* DIO�������� */
        }
        dat >>= 1;

        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK�����ø� */
    }
}

/* TM1628��ȡ1�ֽ� */
uint8_t HDL_TM1628_ReadByte(void)
{
    uint8_t i, dat = 0;

    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);	/* CS�������� */

    for (i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_RESET);   /* CLK�������� */
        HAL_GPIO_WritePin(Port2, GPIO_Pin_4, GPIO_PIN_SET);     /* CLK�����ø� */
        if (GPIO_PIN_SET == HAL_GPIO_ReadPin(Port2, GPIO_Pin_5))	/* ��ȡDIO�ŵ�ƽ */
        {
            dat |= ((uint8_t)0x01);
        }
        dat <<= 1;
    }

    HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);		/* CS�����ø� */

    return dat;
}

/* TM1628�������� */
void HDL_TM1628_SendCMD(uint8_t cmd)
{
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);     /* CS�����ø� */
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_RESET);   /* CS�������� */
	
	HDL_TM1628_WriteByte(cmd);
}
