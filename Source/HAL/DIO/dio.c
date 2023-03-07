#include "dio.h"

void DIO_P0_Init(uint8_t port)
{
	P0M |= (0x01 << port);		/* ���ģʽ */
	P0OC &= ~(0x01 << port);	/* ���ÿ�© */
	P0UR &= ~(0x01 << port);	/* �������� */
}

void DIO_P1_Init(uint8_t port)
{
	P1M |= (0x01 << port);		/* ���ģʽ */
	P1OC &= ~(0x01 << port);	/* ���ÿ�© */
	P1UR &= ~(0x01 << port);	/* �������� */
}

//void DIO_P2_Init(uint8_t port)
//{
//	P2M |= (0x01 << port);		/* ���ģʽ */
//	P2OC &= ~(0x01 << port);	/* ���ÿ�© */
//	P2UR &= ~(0x01 << port);	/* �������� */
//}

