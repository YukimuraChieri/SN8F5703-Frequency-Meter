#include "app_fsm.h"

/* 初始化系统状态 */
SYS_STATUS_E SystemState = SYS_Ready;
KEY_STATUS_E KeyState = KEY_Short;
uint16_t counter = 0;		/* 计数值 */


/* 系统状态机 */
FSM_ACTION_E APP_SystemMachine(uint8_t key_val)
{
	FSM_ACTION_E fsm_action = FSM_No_Action;
	
	switch(SystemState)
	{
		case SYS_Ready: {				/* 系统待命 */
			if (key_val & KEY1)
			{
				SystemState = SYS_KEY1Press;
				KeyState = KEY_Short;
				counter = 0;
				fsm_action = FSM_Freq_Sub;	/* PWM频率减小 */
			}
			else if (key_val & KEY2)
			{
				SystemState = SYS_KEY2Press;
				KeyState = KEY_Short;
				fsm_action = FSM_Freq_Add;	/* PWM频率增加 */
				counter = 0;
			}
		}
		break;
		
		case SYS_KEY1Press: {		/* 按键1按下 */
			if (0 == (key_val & KEY1))
			{
				SystemState = SYS_Ready;
			}
			
			switch(KeyState)		/* 按键子状态机 */
			{
				case KEY_Short: {	/* 按键短按 */
					if (counter > 100)
					{
						KeyState = KEY_Long;
					}
					counter++;
				}
				break;
				
				case KEY_Long: {	/* 按键长按 */
					fsm_action = FSM_Freq_Sub;	/* PWM频率减小 */
				}
				break;
			}
		}
		break;
		
		case SYS_KEY2Press: {		/* 按键2按下 */
			if (0 == (key_val & KEY2))
			{
				SystemState = SYS_Ready;
			}
			
			switch(KeyState)		/* 按键子状态机 */
			{
				case KEY_Short: {	/* 按键短按 */
					if (counter > 100)
					{
						KeyState = KEY_Long;
					}
					counter++;
				}
				break;
				
				case KEY_Long: {	/* 按键长按 */
					fsm_action = FSM_Freq_Add;	/* PWM频率增加 */
				}
				break;
			}
		}
		break;		
	}
	
	return fsm_action;
}
