#include "sn8f5703_hal_delay.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"

uint16_t num = 0;

/* 主函数 */
void main(void)
{
	SystemClock_Init();	/* 初始化系统时钟 */
	
	FML_LED_Init();		/* 初始化LED */
	FML_SEG_Init();		/* 初始化数码管 */
	
	while(1)
	{
		FML_SEG_ShowNum(num);	/* 数码管显示 */
		
		switch (num%8)
		{
			case 0:	FML_LED_Display(LED1);	break;	/* LED1显示 */
			case 1:	FML_LED_Display(LED2);	break;	/* LED1显示 */
			case 2:	FML_LED_Display(LED3);	break;	/* LED1显示 */
			case 3:	FML_LED_Display(LED4);	break;	/* LED1显示 */
			case 4:	FML_LED_Display(LED5);	break;	/* LED1显示 */
			case 5:	FML_LED_Display(LED6);	break;	/* LED1显示 */
			case 6:	FML_LED_Display(LED7);	break;	/* LED1显示 */
			case 7:	FML_LED_Display(LED8);	break;	/* LED1显示 */
		}
		
		HAL_Delay(150);
		
		num++;
	}
}

