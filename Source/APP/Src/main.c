#include "sn8f5703_hal.h"
#include "sn8f5703_hal_pwm.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"

uint16_t num = 0;
uint8_t key_val = 0;

void InitPWM(void);	/* PWM��ʼ������ */

/* ������ */
void main(void)
{
	SystemClock_Init();	/* ��ʼ��ϵͳʱ�� */
	
	InitPWM();	/* PWM��ʼ�� */
	
	FML_KEY_Init();		/* ��ʼ��KEY */
	FML_LED_Init();		/* ��ʼ��LED */
	FML_SEG_Init();		/* ��ʼ������� */
	
	HAL_PWM_Start(PWM_CHANNEL_12);
	
	while(1)
	{
		FML_SEG_ShowNum(key_val);	/* �������ʾ */
		
		key_val = FML_KEY_Scan();
		
		switch (num%8)
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
		
		HAL_Delay(20);
		
		num++;
	}
}


/* PWM��ʼ������ */
void InitPWM(void)
{
	PWM_InitTypeDef PWM_InitStructure;
	/* PWM��ʼ�� */
	PWM_InitStructure.ClockDivision = PWM_CLKDIV_32;		/* Fosc 32��Ƶ */
	PWM_InitStructure.Period = 100;		/* ��������100 */
	PWM_InitStructure.Pulse = 50;			/* �Ƚ�ֵ50 */
	PWM_InitStructure.OCPolarity_1X = PWM1X_OCPolarity_LOW;	/* PWM1X����ת */
	PWM_InitStructure.OCPolarity_2X = PWM2X_OCPolarity_LOW;	/* PWM2X����ת */
	HAL_PWM_Init(&PWM_InitStructure);

//	/* PWMʱ�ӷ�Ƶ���� */
//	PW1M |= 0x20;
//	/* PWM�������� */
//	PW1YL = 8;
//	PW1YH = 0;
//	/* PWMռ�ձ����� */
//	PW1DL = 4;
//	PW1DH = 0;
}

