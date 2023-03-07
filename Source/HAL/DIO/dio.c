#include "dio.h"

void DIO_P0_Init(uint8_t port)
{
	P0M |= (0x01 << port);		/* 输出模式 */
	P0OC &= ~(0x01 << port);	/* 禁用开漏 */
	P0UR &= ~(0x01 << port);	/* 禁用上拉 */
}

void DIO_P1_Init(uint8_t port)
{
	P1M |= (0x01 << port);		/* 输出模式 */
	P1OC &= ~(0x01 << port);	/* 禁用开漏 */
	P1UR &= ~(0x01 << port);	/* 禁用上拉 */
}

//void DIO_P2_Init(uint8_t port)
//{
//	P2M |= (0x01 << port);		/* 输出模式 */
//	P2OC &= ~(0x01 << port);	/* 禁用开漏 */
//	P2UR &= ~(0x01 << port);	/* 禁用上拉 */
//}

