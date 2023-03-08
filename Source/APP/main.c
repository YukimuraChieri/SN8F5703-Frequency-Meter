#include "SN8F5703.h"
//#include "key.h"
//#include "led.h"
//#include "seg.h"

/* 毫秒级延时函数 */
void delay_ms(uint16_t tm)
{
	uint16_t i, j;
	for (i = 0; i < tm; i++)
	{
		for (j = 0; j < 1000; j++);
	}
}

/* 初始化系统时钟 */
void system_init(void)
{
	CKCON = 0x70;		/* For change safely the system clock */
	CLKSEL = 0x05;	/* Fcpu=Fosc/4=8MHz */
	CLKCMD = 0x69;	/* Apply CLKSEL’s setting */
	CKCON = 0x00;		/* IROM fetch = fcpu / 1 */
}

void func(uint8_t port)
{
	port++;
}
	
/* 主函数 */
int main(void)
{
	system_init();	/* 初始化系统时钟 */
	
	P0M |= (0x01 << 4);		/* 输出模式 */
	P0OC &= ~(0x01 << 4);	/* 禁用开漏 */
	P0UR &= ~(0x01 << 4);	/* 禁用上拉 */	
	
	while(1)
	{
		P04 = 1;
		delay_ms(1000);
		P04 = 0;
		delay_ms(1000);
	}
	
	return 0;
}

