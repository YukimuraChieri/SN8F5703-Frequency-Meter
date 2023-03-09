#include "sn8f5703_hal_delay.h"
#include "sn8f5703_hal_gpio.h"
#include "fml_key.h"
#include "fml_led.h"
#include "fml_seg.h"

/* ������ */
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	SystemClock_Init();	/* ��ʼ��ϵͳʱ�� */

	/* P04���ų�ʼ�� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = GPIO_Pin_4;
    GPIO_InitStructure.Pull = 1;
    HAL_GPIO_Init(Port0, &GPIO_InitStructure);
	
	while(1)
	{
		HAL_GPIO_WritePin(Port0, GPIO_Pin_4, GPIO_PIN_SET);
		delay_ms(1000);
		HAL_GPIO_WritePin(Port0, GPIO_Pin_4, GPIO_PIN_RESET);
		delay_ms(1000);
	}
	
	return 0;
}

