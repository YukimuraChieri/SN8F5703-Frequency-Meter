#ifndef __SN8F5703_HAL_GPIO_H
#define __SN8F5703_HAL_GPIO_H

#include "SN8F5703.h"

#define GPIO_PIN_SET    1
#define GPIO_PIN_RESET  0

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
  GPIO_MODE_INPUT,			/* ����ģʽ */
  GPIO_MODE_OUTPUT_PP,	/* �������ģʽ */
  GPIO_MODE_OUTPUT_OC,	/* �����©ģʽ */
}GPIO_ModeTypeDef;

typedef enum
{
  Port0,                /* P0�˿� */
  Port1,                /* P1�˿� */
  Port2,                /* P2�˿� */
}GPIO_PortTypeDef;

typedef struct
{
	uint8_t Pin;
	GPIO_ModeTypeDef Mode;
	uint8_t Pull;
}GPIO_InitTypeDef;

void HAL_GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_InitTypeDef* GPIO_Init);
void HAL_GPIO_WritePin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin, uint8_t pinState);
uint8_t HAL_GPIO_ReadPin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin);

#endif
