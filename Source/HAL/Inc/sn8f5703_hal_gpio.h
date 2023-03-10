#ifndef __SN8F5703_HAL_GPIO_H
#define __SN8F5703_HAL_GPIO_H

#include "SN8F5703.h"

/* ����״̬���� */
typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
}GPIO_PinState;

/* ���Ŷ��� */
#define GPIO_Pin_0		((uint8_t)0x01)  /*!< Pin 0 selected */
#define GPIO_Pin_1		((uint8_t)0x02)  /*!< Pin 1 selected */
#define GPIO_Pin_2		((uint8_t)0x04)  /*!< Pin 2 selected */
#define GPIO_Pin_3		((uint8_t)0x08)  /*!< Pin 3 selected */
#define GPIO_Pin_4		((uint8_t)0x10)  /*!< Pin 4 selected */
#define GPIO_Pin_5		((uint8_t)0x20)  /*!< Pin 5 selected */
#define GPIO_Pin_6		((uint8_t)0x40)  /*!< Pin 6 selected */
#define GPIO_Pin_7		((uint8_t)0x80)  /*!< Pin 7 selected */
#define GPIO_PIN_All	((uint8_t)0xFF)  /* All pins selected */

/* ������������ */
#define GPIO_NOPULL     0u
#define GPIO_PULLUP     1u

/* GPIOģʽö�� */
typedef enum
{
  GPIO_MODE_INPUT,			/* ����ģʽ */
  GPIO_MODE_OUTPUT_PP,	/* �������ģʽ */
  GPIO_MODE_OUTPUT_OC,	/* �����©ģʽ */
}GPIO_ModeTypeDef;

/* GPIO�˿�ö�� */
typedef enum
{
  Port0,                /* P0�˿� */
  Port1,                /* P1�˿� */
  Port2,                /* P2�˿� */
}GPIO_PortTypeDef;

/* GPIO���ýṹ�� */
typedef struct
{
	uint8_t Pin;
	GPIO_ModeTypeDef Mode;
	uint8_t Pull;
}GPIO_InitTypeDef;

/* HAL��GPIOģ��ӿں��� */
void HAL_GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_InitTypeDef* GPIO_Init);
void HAL_GPIO_WritePin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin, uint8_t pinState);
uint8_t HAL_GPIO_ReadPin(GPIO_PortTypeDef GPIOx, uint8_t GPIO_Pin);

#endif

