#include "sn8f5703_hal.h"
#include "sn8f5703_hal_pwm.h"
#include "sn8f5703_hal_tim.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"
#include "app_fsm.h"
#include <string.h>

#define FOSC 32000000U		/* OSC频率 */
#define FCPU 8000000U			/* CPU频率 */
#define MeasurementPeriod 1000U	/* 检测循环次数 */
#define MAX_FREQ	10000U	/* 最大频率 */
#define MIN_FREQ	20U			/* 最小频率 */

/* 函数声明 */
void InitPWM(void);								/* PWM初始化函数 */
void InitTIM2_IC1(void);					/* 初始化定时器2 IC1 */
void LED_Ring_Disp(uint8_t dir);	/* LED环形显示 */
uint16_t MeasurementFreq(void);		/* 频率测量 */
uint16_t median_filter(uint16_t dat);		/* 中值滤波 */

/* 全局变量 */
FSM_ACTION_E fsm_action = FSM_No_Action;
uint16_t pwm_output_frep = 1000;
uint16_t pwm_input_frep = 0;
uint16_t pwm_period = 0;
uint16_t pwm_compare = 0;
uint8_t key_val = 0;
uint8_t led_disp_period = 0;
uint8_t zero_cnt = 0;								/* 零频计数值 */
uint16_t real_input_freq = 0;				/* 实际频率 */

/* 主函数 */
void main(void)
{
	SystemClock_Init();	/* 初始化系统时钟 */
	
	FML_KEY_Init();			/* 初始化KEY */
	FML_LED_Init();			/* 初始化LED */
	FML_SEG_Init();			/* 初始化数码管 */
	
	InitPWM();					/* PWM初始化 */
	InitTIM2_IC1();			/* 初始化定时器2 IC1 */
	
	while(1)
	{
		key_val = FML_KEY_Scan();	/* 按键扫描 */
		
		fsm_action = APP_SystemMachine(key_val);	/* 系统状态机 */
		
		switch (fsm_action)	/* 状态机动作执行 */
		{
			case FSM_Freq_Add: {	/* 频率增加 */
				if (pwm_output_frep < MAX_FREQ)
				{
					pwm_output_frep += 5;		/* 输出PWM频率加5 */
					pwm_period = (FOSC/ 32 / pwm_output_frep);
					pwm_compare = pwm_period >> 1;
					
					HAL_PWM_Set_Compare(pwm_compare);	/* 设置比较值 */
					HAL_PWM_Set_Period(pwm_period);		/* 设置周期值 */
					
					if (0 == (led_disp_period % 5))		/* 每增加5次，LED显示改变 */
					{
						LED_Ring_Disp(1);
					}
					led_disp_period++;
				}
			}
			break;
			
			case FSM_Freq_Sub: {	/* 频率减小 */
				if (pwm_output_frep > MIN_FREQ)
				{
					pwm_output_frep -= 5;		/* 输出PWM频率减5 */
					pwm_period = (FOSC/ 32 / pwm_output_frep);
					pwm_compare = pwm_period >> 1;
					
					HAL_PWM_Set_Period(pwm_period);		/* 设置周期值 */
					HAL_PWM_Set_Compare(pwm_compare);	/* 设置比较值 */
					
					if (0 == (led_disp_period % 5))		/* 每减小5次，LED显示改变 */
					{
						LED_Ring_Disp(0);
					}
					led_disp_period++;
				}
			}
			break;
			
			case FSM_No_Action: {	/* 无动作 */
			}
			break;
		}
		
		
		/* 频率测量 */
		pwm_input_frep = MeasurementFreq();
		
		if (0 != pwm_input_frep)	/* 如果测量结果不为0 */
		{
			pwm_input_frep = median_filter(pwm_input_frep);	/* 中值滤波 */
			real_input_freq = pwm_input_frep;
			zero_cnt = 0;		/* 零频计数值清0 */
		}
		else
		{
			if (zero_cnt < 16)
			{
				zero_cnt++;		/* 零频计数值加1 */
			}
		}
		
		if (zero_cnt > 15)	/* 零频计数值超过10，判断此时已经断开连线 */
		{
			real_input_freq = 0;
		}
		
		FML_SEG_ShowNum(real_input_freq);	/* 数码管显示测量结果 */
		
		HAL_Delay(8);	/* 延时8ms */
	}
}

/* PWM初始化函数 */
void InitPWM(void)
{
	PWM_InitTypeDef PWM_InitStructure;
	
	/* 计算PWM周期值和比较值 */
	pwm_period = (1000000 / pwm_output_frep);
	pwm_compare = pwm_period >> 1;
	
	/* PWM配置 */
	PWM_InitStructure.ClockDivision = PWM_FOSC_DIV32;		/* Fosc 32分频 */
	PWM_InitStructure.Period = pwm_period;		/* 设置PWM周期 */
	PWM_InitStructure.Pulse = pwm_compare;		/* 设置PWM比较值 */
	PWM_InitStructure.OCPolarity_1X = PWM1X_OCPolarity_LOW;	/* PWM1X不反转 */
	PWM_InitStructure.OCPolarity_2X = PWM2X_OCPolarity_LOW;	/* PWM2X不反转 */
	/* PWM初始化 */
	HAL_PWM_Init(&PWM_InitStructure);
	
	HAL_PWM_Start(PWM_CHANNEL_12);		/* PWM12开始输出 */
}

/* 初始化定时器2 IC1 */
void InitTIM2_IC1(void)
{
	TIM2_Base_InitTypeDef TIM2_Base_InitStructure;
	TIM2_IC_InitTypeDef TIM2_IC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* TIM2 IC1引脚初始化 */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;  	/* 推挽输出 */
	GPIO_InitStructure.Pin = GPIO_Pin_1;					/* Pin1脚 */
	GPIO_InitStructure.Pull = GPIO_PULLUP;				/* 使能上拉 */
	HAL_GPIO_Init(Port0, &GPIO_InitStructure);
	
	/* TIM2 Base配置 */	
	TIM2_Base_InitStructure.Prescaler = TIM2_FCPU_DIV12;	/* FCPU12分频 */
	TIM2_Base_InitStructure.AutoReloadPreload = TIM2_AUTORELOAD_PRELOAD_COUNTER;	/* 自动重装载 */
	TIM2_Base_InitStructure.ClockSource = TIM2_CLK_FCPU;	/* 时钟源为FCPU */
	TIM2_Base_InitStructure.Period = (uint16_t)0x0000;		/* 计数器清0 */
	
	/* TIM2 IC配置 */
	TIM2_IC_InitStructure.ICPolarity = TIM2_ICPOLARITY_RISING;	/* 上升沿捕获 */
	TIM2_IC_InitStructure.ICSelection = TIM2_IC_CHANNEL_1;			/* IC通道1 */
	
	/* 初始化TIM2 Base和IC */
	HAL_TIM2_Base_Init(&TIM2_Base_InitStructure);
	HAL_TIM2_IC_Init(&TIM2_IC_InitStructure);
}

/* 
	LED环形显示 
	dir = 1 : 顺时针旋转一格
	dir = 0 :	逆时针旋转一格
*/
void LED_Ring_Disp(uint8_t dir)
{
	static uint8_t index = 0;
		
	if (1 == dir)	/* 顺时针旋转 */
	{
		index = (index + 1) % 8;
	}
	else					/* 逆时针旋转 */
	{
		if (0 == index)
		{
			index = 7;
		}
		else
		{
			index--;
		}
	}
	
	/* LED显示 */
	switch (index)
	{
		case 0:	FML_LED_Display(LED1);	break;	/* LED1显示 */
		case 1:	FML_LED_Display(LED2);	break;	/* LED2显示 */
		case 2:	FML_LED_Display(LED3);	break;	/* LED3显示 */
		case 3:	FML_LED_Display(LED4);	break;	/* LED4显示 */
		case 4:	FML_LED_Display(LED5);	break;	/* LED5显示 */
		case 5:	FML_LED_Display(LED6);	break;	/* LED6显示 */
		case 6:	FML_LED_Display(LED7);	break;	/* LED7显示 */
		case 7:	FML_LED_Display(LED8);	break;	/* LED8显示 */
	}
}

/* 频率测量 */
uint16_t MeasurementFreq(void)
{
	uint16_t captured_value[2] = {0};
	uint16_t t, freq = 0;
	uint16_t delta_value = 0;
	
	captured_value[0] = HAL_TIM2_ReadCapturedValue(TIM2_IC_CHANNEL_1);
	captured_value[1] = captured_value[0];
	for (t = 0; t < MeasurementPeriod; t++)
	{
		captured_value[0] = HAL_TIM2_ReadCapturedValue(TIM2_IC_CHANNEL_1);
		if (captured_value[0] > captured_value[1])
		{
			delta_value = captured_value[0] - captured_value[1];
			freq = FCPU / 12 / delta_value;
			break;
		}
	}
	return freq;
}

/* 中值滤波 */
uint16_t median_filter(uint16_t dat)
{
	static uint16_t raw_data[8] = {0};
	uint16_t temp_buff[8];
	uint16_t temp;
	uint8_t i, j;	
	
	/* 原始数据窗口移位 */
	for (i = 0; i < 7; i++)
	{
		raw_data[7-i] = raw_data[6-i];
	}
	raw_data[0] = dat;
	
	/* 原始数据复制到temp_buff */
	memcpy(temp_buff, raw_data, 8*sizeof(uint16_t));
	
	/* 数据排序 */
	for (i = 0; i < 7; i++)
	{
		for (j = i+1; j < 8; j++)
		{
			if (temp_buff[i] > temp_buff[j])
			{
				temp = temp_buff[i];
				temp_buff[i] = temp_buff[j];
				temp_buff[j] = temp;
			}
		}
	}
	
	/* 返回中位数 */
	return (temp_buff[3] + temp_buff[4]) / 2;
}