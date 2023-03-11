#include "app_fsm.h"

/* ��ʼ��ϵͳ״̬ */
SYS_STATUS_E SystemState = SYS_Ready;
KEY_STATUS_E KeyState = KEY_Short;
uint16_t counter = 0;		/* ����ֵ */


/* ϵͳ״̬�� */
FSM_ACTION_E APP_SystemMachine(uint8_t key_val)
{
	FSM_ACTION_E fsm_action = FSM_No_Action;
	
	switch(SystemState)
	{
		case SYS_Ready: {				/* ϵͳ���� */
			if (key_val & KEY1)
			{
				SystemState = SYS_KEY1Press;
				KeyState = KEY_Short;
				counter = 0;
				fsm_action = FSM_Freq_Sub;	/* PWMƵ�ʼ�С */
			}
			else if (key_val & KEY2)
			{
				SystemState = SYS_KEY2Press;
				KeyState = KEY_Short;
				fsm_action = FSM_Freq_Add;	/* PWMƵ������ */
				counter = 0;
			}
		}
		break;
		
		case SYS_KEY1Press: {		/* ����1���� */
			if (0 == (key_val & KEY1))
			{
				SystemState = SYS_Ready;
			}
			
			switch(KeyState)		/* ������״̬�� */
			{
				case KEY_Short: {	/* �����̰� */
					if (counter > 100)
					{
						KeyState = KEY_Long;
					}
					counter++;
				}
				break;
				
				case KEY_Long: {	/* �������� */
					fsm_action = FSM_Freq_Sub;	/* PWMƵ�ʼ�С */
				}
				break;
			}
		}
		break;
		
		case SYS_KEY2Press: {		/* ����2���� */
			if (0 == (key_val & KEY2))
			{
				SystemState = SYS_Ready;
			}
			
			switch(KeyState)		/* ������״̬�� */
			{
				case KEY_Short: {	/* �����̰� */
					if (counter > 100)
					{
						KeyState = KEY_Long;
					}
					counter++;
				}
				break;
				
				case KEY_Long: {	/* �������� */
					fsm_action = FSM_Freq_Add;	/* PWMƵ������ */
				}
				break;
			}
		}
		break;		
	}
	
	return fsm_action;
}
