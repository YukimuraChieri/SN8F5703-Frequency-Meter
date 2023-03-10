#ifndef __FML_KEY_H
#define __FML_KEY_H

#include "hdl_tm1628.h"

/* ���尴��ֵ */
#define KEY1	((uint8_t)0x01)
#define KEY2	((uint8_t)0x02)
#define KEY3	((uint8_t)0x04)
#define KEY4	((uint8_t)0x08)

void FML_KEY_Init(void);    /* ��ʼ������ */
uint8_t FML_KEY_Scan(void); /* ����ɨ�� */


#endif
