#ifndef __FML_SEG_H
#define __FML_SEG_H

#include "hdl_tm1628.h"

/* FML��SEGģ��ӿں��� */
void FML_SEG_Init(void);		/* ��ʼ������� */
void FML_SEG_Display(uint8_t dig, uint8_t seg);	/* ����ܵ�����ʾ */
void FML_SEG_ShowNum(uint16_t num);	/* �������ʾ���� */

#endif
