#include "SN8F5703.h"
//#include "key.h"
//#include "led.h"
//#include "seg.h"

/* ���뼶��ʱ���� */
void delay_ms(uint16_t tm)
{
	uint16_t i, j;
	for (i = 0; i < tm; i++)
	{
		for (j = 0; j < 1000; j++);
	}
}

/* ��ʼ��ϵͳʱ�� */
void system_init(void)
{
	CKCON = 0x70;		/* For change safely the system clock */
	CLKSEL = 0x05;	/* Fcpu=Fosc/4=8MHz */
	CLKCMD = 0x69;	/* Apply CLKSEL��s setting */
	CKCON = 0x00;		/* IROM fetch = fcpu / 1 */
}

void func(uint8_t port)
{
	port++;
}
	
/* ������ */
int main(void)
{
	system_init();	/* ��ʼ��ϵͳʱ�� */
	
	P0M |= (0x01 << 4);		/* ���ģʽ */
	P0OC &= ~(0x01 << 4);	/* ���ÿ�© */
	P0UR &= ~(0x01 << 4);	/* �������� */	
	
	while(1)
	{
		P04 = 1;
		delay_ms(1000);
		P04 = 0;
		delay_ms(1000);
	}
	
	return 0;
}

