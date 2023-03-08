#ifndef __DIO_H
#define __DIO_H

#include "SN8F5703.h"

#define GPIO_Pin_0	((uint8_t)0x01)  /*!< Pin 0 selected */
#define GPIO_Pin_1	((uint8_t)0x02)  /*!< Pin 1 selected */
#define GPIO_Pin_2	((uint8_t)0x04)  /*!< Pin 2 selected */
#define GPIO_Pin_3	((uint8_t)0x08)  /*!< Pin 3 selected */
#define GPIO_Pin_4	((uint8_t)0x10)  /*!< Pin 4 selected */
#define GPIO_Pin_5	((uint8_t)0x20)  /*!< Pin 5 selected */
#define GPIO_Pin_6	((uint8_t)0x40)  /*!< Pin 6 selected */
#define GPIO_Pin_7	((uint8_t)0x80)  /*!< Pin 7 selected */

typedef enum
{
  GPIO_MODE_INPUT,			/* 输入模式 */
  GPIO_MODE_OUTPUT_PP,	/* 输出推挽模式 */
  GPIO_MODE_OUTPUT_OC,	/* 输出开漏模式 */
}GPIO_ModeTypeDef;

typedef struct
{
	uint8_t Pin;
	GPIO_ModeTypeDef Mode;
	uint8_t Pull;
}GPIO_InitTypeDef;

#define HAL_GPIO_WritePin(port, pin, pinState) (port)=(pinState)
#define HAL_GPIO_ReadPin(port, pin) (port)
void HAL_GPIO_Init(uint8_t GPIOx, GPIO_InitTypeDef* GPIO_Init);

#endif

