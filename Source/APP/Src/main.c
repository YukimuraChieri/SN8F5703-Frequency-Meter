#include "sn8f5703_hal.h"
#include "sn8f5703_hal_pwm.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"

uint16_t num = 0;
uint8_t key_val = 0;

void InitPWM(void);	/* PWM初始化函数 */

/* 主函数 */
void main(void)
{
	SystemClock_Init();	/* 初始化系统时钟 */
	
	InitPWM();	/* PWM初始化 */
	
	FML_KEY_Init();		/* 初始化KEY */
	FML_LED_Init();		/* 初始化LED */
	FML_SEG_Init();		/* 初始化数码管 */
	
	HAL_PWM_Start(PWM_CHANNEL_12);
	
	while(1)
	{
		FML_SEG_ShowNum(key_val);	/* 数码管显示 */
		
		key_val = FML_KEY_Scan();
		
		switch (num%8)
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
		
		HAL_Delay(20);
		
		num++;
	}
}


/* PWM初始化函数 */
void InitPWM(void)
{
	PWM_InitTypeDef PWM_InitStructure;
	/* PWM初始化 */
	PWM_InitStructure.ClockDivision = PWM_CLKDIV_32;		/* Fosc 32分频 */
	PWM_InitStructure.Period = 100;		/* 计数周期100 */
	PWM_InitStructure.Pulse = 50;			/* 比较值50 */
	PWM_InitStructure.OCPolarity_1X = PWM1X_OCPolarity_LOW;	/* PWM1X不反转 */
	PWM_InitStructure.OCPolarity_2X = PWM2X_OCPolarity_LOW;	/* PWM2X不反转 */
	HAL_PWM_Init(&PWM_InitStructure);

//	/* PWM时钟分频设置 */
//	PW1M |= 0x20;
//	/* PWM周期设置 */
//	PW1YL = 8;
//	PW1YH = 0;
//	/* PWM占空比设置 */
//	PW1DL = 4;
//	PW1DH = 0;
}

