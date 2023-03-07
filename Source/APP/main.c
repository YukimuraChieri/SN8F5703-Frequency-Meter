#include "SN8F5703.h"
#include "key.h"
#include "led.h"
#include "seg.h"

void delay_ms(uint16_t tm)
{
	uint16_t i, j;
	for (i = 0; i < tm; i++)
	{
		for (j = 0; j < 800; j++);
	}
}

int main(void)
{
	while(1)
	{
		;
	}
	return 0;
}

