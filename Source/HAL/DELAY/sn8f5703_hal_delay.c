#include "sn8f5703_hal_delay.h"

/* ��ʼ��ϵͳʱ�� */
void SystemClock_Init(void)
{
	CKCON = 0x70;   /* For change safely the system clock */
	CLKSEL = 0x05;	/* Fcpu=Fosc/4=8MHz */
	CLKCMD = 0x69;	/* Apply CLKSEL��s setting */
	CKCON = 0x00;   /* IROM fetch = fcpu / 1 */
}

/* ���뼶��ʱ���� */
void HAL_Delay(uint16_t Delay)
{
    uint16_t i, j;
	for (i = 0; i < Delay; i++)
	{
		for (j = 0; j < 1000; j++);
	}
}
