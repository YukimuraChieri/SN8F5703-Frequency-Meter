#ifndef __APP_FSM_H
#define __APP_FSM_H

#include "fml_key.h"

/* 系统状态枚举定义 */
typedef enum
{
	SYS_Ready,			/* 待命 */
	SYS_KEY1Press,	/* 按键1按下 */
	SYS_KEY2Press,	/* 按键2按下 */
}SYS_STATUS_E;

/* 按键状态枚举定义 */
typedef enum
{
	KEY_Short,	/* 按键短按 */
	KEY_Long,		/* 按键长按 */
}KEY_STATUS_E;

/* 状态机执行动作枚举 */
typedef enum
{
	FSM_Freq_Add,		/* 频率增加 */
	FSM_Freq_Sub,		/* 频率减小 */
	FSM_No_Action,	/* 无动作 */
}FSM_ACTION_E;


/* APP层FSM模块接口函数 */
FSM_ACTION_E APP_SystemMachine(uint8_t key_val);	/* 系统状态机 */


#endif

