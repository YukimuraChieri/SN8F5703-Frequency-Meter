#ifndef __APP_FSM_H
#define __APP_FSM_H

#include "fml_key.h"

/* ϵͳ״̬ö�ٶ��� */
typedef enum
{
	SYS_Ready,			/* ���� */
	SYS_KEY1Press,	/* ����1���� */
	SYS_KEY2Press,	/* ����2���� */
}SYS_STATUS_E;

/* ����״̬ö�ٶ��� */
typedef enum
{
	KEY_Short,	/* �����̰� */
	KEY_Long,		/* �������� */
}KEY_STATUS_E;

/* ״̬��ִ�ж���ö�� */
typedef enum
{
	FSM_Freq_Add,		/* Ƶ������ */
	FSM_Freq_Sub,		/* Ƶ�ʼ�С */
	FSM_No_Action,	/* �޶��� */
}FSM_ACTION_E;


/* APP��FSMģ��ӿں��� */
FSM_ACTION_E APP_SystemMachine(uint8_t key_val);	/* ϵͳ״̬�� */


#endif

