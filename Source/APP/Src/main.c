#include "sn8f5703_hal.h"
#include "sn8f5703_hal_pwm.h"
#include "sn8f5703_hal_tim.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"
#include "app_fsm.h"
#include <string.h>

#define FOSC 32000000U		/* OSCƵ�� */
#define FCPU 8000000U			/* CPUƵ�� */
#define MeasurementPeriod 1000U	/* ���ѭ������ */
#define MAX_FREQ	10000U	/* ���Ƶ�� */
#define MIN_FREQ	20U			/* ��СƵ�� */

/* �������� */
void InitPWM(void);								/* PWM��ʼ������ */
void InitTIM2_IC1(void);					/* ��ʼ����ʱ��2 IC1 */
void LED_Ring_Disp(uint8_t dir);	/* LED������ʾ */
uint16_t MeasurementFreq(void);		/* Ƶ�ʲ��� */
uint16_t median_filter(uint16_t dat);		/* ��ֵ�˲� */

/* ȫ�ֱ��� */
FSM_ACTION_E fsm_action = FSM_No_Action;
uint16_t pwm_output_frep = 1000;
uint16_t pwm_input_frep = 0;
uint16_t pwm_period = 0;
uint16_t pwm_compare = 0;
uint8_t key_val = 0;
uint8_t led_disp_period = 0;
uint8_t zero_cnt = 0;								/* ��Ƶ����ֵ */
uint16_t real_input_freq = 0;				/* ʵ��Ƶ�� */

/* ������ */
void main(void)
{
	SystemClock_Init();	/* ��ʼ��ϵͳʱ�� */
	
	FML_KEY_Init();			/* ��ʼ��KEY */
	FML_LED_Init();			/* ��ʼ��LED */
	FML_SEG_Init();			/* ��ʼ������� */
	
	InitPWM();					/* PWM��ʼ�� */
	InitTIM2_IC1();			/* ��ʼ����ʱ��2 IC1 */
	
	while(1)
	{
		key_val = FML_KEY_Scan();	/* ����ɨ�� */
		
		fsm_action = APP_SystemMachine(key_val);	/* ϵͳ״̬�� */
		
		switch (fsm_action)	/* ״̬������ִ�� */
		{
			case FSM_Freq_Add: {	/* Ƶ������ */
				if (pwm_output_frep < MAX_FREQ)
				{
					pwm_output_frep += 5;		/* ���PWMƵ�ʼ�5 */
					pwm_period = (FOSC/ 32 / pwm_output_frep);
					pwm_compare = pwm_period >> 1;
					
					HAL_PWM_Set_Compare(pwm_compare);	/* ���ñȽ�ֵ */
					HAL_PWM_Set_Period(pwm_period);		/* ��������ֵ */
					
					if (0 == (led_disp_period % 5))		/* ÿ����5�Σ�LED��ʾ�ı� */
					{
						LED_Ring_Disp(1);
					}
					led_disp_period++;
				}
			}
			break;
			
			case FSM_Freq_Sub: {	/* Ƶ�ʼ�С */
				if (pwm_output_frep > MIN_FREQ)
				{
					pwm_output_frep -= 5;		/* ���PWMƵ�ʼ�5 */
					pwm_period = (FOSC/ 32 / pwm_output_frep);
					pwm_compare = pwm_period >> 1;
					
					HAL_PWM_Set_Period(pwm_period);		/* ��������ֵ */
					HAL_PWM_Set_Compare(pwm_compare);	/* ���ñȽ�ֵ */
					
					if (0 == (led_disp_period % 5))		/* ÿ��С5�Σ�LED��ʾ�ı� */
					{
						LED_Ring_Disp(0);
					}
					led_disp_period++;
				}
			}
			break;
			
			case FSM_No_Action: {	/* �޶��� */
			}
			break;
		}
		
		
		/* Ƶ�ʲ��� */
		pwm_input_frep = MeasurementFreq();
		
		if (0 != pwm_input_frep)	/* ������������Ϊ0 */
		{
			pwm_input_frep = median_filter(pwm_input_frep);	/* ��ֵ�˲� */
			real_input_freq = pwm_input_frep;
			zero_cnt = 0;		/* ��Ƶ����ֵ��0 */
		}
		else
		{
			if (zero_cnt < 16)
			{
				zero_cnt++;		/* ��Ƶ����ֵ��1 */
			}
		}
		
		if (zero_cnt > 15)	/* ��Ƶ����ֵ����10���жϴ�ʱ�Ѿ��Ͽ����� */
		{
			real_input_freq = 0;
		}
		
		FML_SEG_ShowNum(real_input_freq);	/* �������ʾ������� */
		
		HAL_Delay(8);	/* ��ʱ8ms */
	}
}

/* PWM��ʼ������ */
void InitPWM(void)
{
	PWM_InitTypeDef PWM_InitStructure;
	
	/* ����PWM����ֵ�ͱȽ�ֵ */
	pwm_period = (1000000 / pwm_output_frep);
	pwm_compare = pwm_period >> 1;
	
	/* PWM���� */
	PWM_InitStructure.ClockDivision = PWM_FOSC_DIV32;		/* Fosc 32��Ƶ */
	PWM_InitStructure.Period = pwm_period;		/* ����PWM���� */
	PWM_InitStructure.Pulse = pwm_compare;		/* ����PWM�Ƚ�ֵ */
	PWM_InitStructure.OCPolarity_1X = PWM1X_OCPolarity_LOW;	/* PWM1X����ת */
	PWM_InitStructure.OCPolarity_2X = PWM2X_OCPolarity_LOW;	/* PWM2X����ת */
	/* PWM��ʼ�� */
	HAL_PWM_Init(&PWM_InitStructure);
	
	HAL_PWM_Start(PWM_CHANNEL_12);		/* PWM12��ʼ��� */
}

/* ��ʼ����ʱ��2 IC1 */
void InitTIM2_IC1(void)
{
	TIM2_Base_InitTypeDef TIM2_Base_InitStructure;
	TIM2_IC_InitTypeDef TIM2_IC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* TIM2 IC1���ų�ʼ�� */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;  	/* ������� */
	GPIO_InitStructure.Pin = GPIO_Pin_1;					/* Pin1�� */
	GPIO_InitStructure.Pull = GPIO_PULLUP;				/* ʹ������ */
	HAL_GPIO_Init(Port0, &GPIO_InitStructure);
	
	/* TIM2 Base���� */	
	TIM2_Base_InitStructure.Prescaler = TIM2_FCPU_DIV12;	/* FCPU12��Ƶ */
	TIM2_Base_InitStructure.AutoReloadPreload = TIM2_AUTORELOAD_PRELOAD_COUNTER;	/* �Զ���װ�� */
	TIM2_Base_InitStructure.ClockSource = TIM2_CLK_FCPU;	/* ʱ��ԴΪFCPU */
	TIM2_Base_InitStructure.Period = (uint16_t)0x0000;		/* ��������0 */
	
	/* TIM2 IC���� */
	TIM2_IC_InitStructure.ICPolarity = TIM2_ICPOLARITY_RISING;	/* �����ز��� */
	TIM2_IC_InitStructure.ICSelection = TIM2_IC_CHANNEL_1;			/* ICͨ��1 */
	
	/* ��ʼ��TIM2 Base��IC */
	HAL_TIM2_Base_Init(&TIM2_Base_InitStructure);
	HAL_TIM2_IC_Init(&TIM2_IC_InitStructure);
}

/* 
	LED������ʾ 
	dir = 1 : ˳ʱ����תһ��
	dir = 0 :	��ʱ����תһ��
*/
void LED_Ring_Disp(uint8_t dir)
{
	static uint8_t index = 0;
		
	if (1 == dir)	/* ˳ʱ����ת */
	{
		index = (index + 1) % 8;
	}
	else					/* ��ʱ����ת */
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
	
	/* LED��ʾ */
	switch (index)
	{
		case 0:	FML_LED_Display(LED1);	break;	/* LED1��ʾ */
		case 1:	FML_LED_Display(LED2);	break;	/* LED2��ʾ */
		case 2:	FML_LED_Display(LED3);	break;	/* LED3��ʾ */
		case 3:	FML_LED_Display(LED4);	break;	/* LED4��ʾ */
		case 4:	FML_LED_Display(LED5);	break;	/* LED5��ʾ */
		case 5:	FML_LED_Display(LED6);	break;	/* LED6��ʾ */
		case 6:	FML_LED_Display(LED7);	break;	/* LED7��ʾ */
		case 7:	FML_LED_Display(LED8);	break;	/* LED8��ʾ */
	}
}

/* Ƶ�ʲ��� */
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

/* ��ֵ�˲� */
uint16_t median_filter(uint16_t dat)
{
	static uint16_t raw_data[8] = {0};
	uint16_t temp_buff[8];
	uint16_t temp;
	uint8_t i, j;	
	
	/* ԭʼ���ݴ�����λ */
	for (i = 0; i < 7; i++)
	{
		raw_data[7-i] = raw_data[6-i];
	}
	raw_data[0] = dat;
	
	/* ԭʼ���ݸ��Ƶ�temp_buff */
	memcpy(temp_buff, raw_data, 8*sizeof(uint16_t));
	
	/* �������� */
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
	
	/* ������λ�� */
	return (temp_buff[3] + temp_buff[4]) / 2;
}