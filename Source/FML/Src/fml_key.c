#include "fml_key.h"

uint8_t key_buf[5] = {0};

/* ��ʼ������ */
void FML_KEY_Init(void)
{
	HDL_TM1628_Init();  /* ��ʼ��TM1628 */
}

/* ����ɨ�� */
uint8_t FML_KEY_Scan(void)
{
	uint8_t key_val = 0, i;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	HDL_TM1628_SendCMD(0x42);	/* TM1628���������� */
	
	/* TM1628 DIO���������������� */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;  /* ���� */
	GPIO_InitStructure.Pin = GPIO_Pin_5;				/* Pin5�� */
	GPIO_InitStructure.Pull = GPIO_NOPULL;			/* �������� */
	HAL_GPIO_Init(Port2, &GPIO_InitStructure);
	
	for (i = 0; i < 5; i++)
	{
		key_buf[i] = HDL_TM1628_ReadByte();	/* TM1628��ȡ���� */	
	}
	
	/* TM1628 DIO�������ų�ʼ�� */
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  /* ������� */
	GPIO_InitStructure.Pin = GPIO_Pin_5;            /* Pin5�� */
	GPIO_InitStructure.Pull = GPIO_NOPULL;          /* �������� */
	HAL_GPIO_Init(Port2, &GPIO_InitStructure);
	
	HAL_GPIO_WritePin(Port2, GPIO_Pin_0, GPIO_PIN_SET);	/* CS�����ø� */
	
	if (key_buf[1] & 0x08)	/* ��ⰴ��1 */
	{
		key_val |= KEY1;
	}
	if (key_buf[3] & 0x08)	/* ��ⰴ��2 */
	{
		key_val |= KEY2;
	}
	if (key_buf[3] & 0x01)	/* ��ⰴ��3 */
	{
		key_val |= KEY3;
	}
	if (key_buf[1] & 0x01)	/* ��ⰴ��4 */
	{
		key_val |= KEY4;
	}
	
	return key_val;
}
