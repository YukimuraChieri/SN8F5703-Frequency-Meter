#ifndef __SN8F5703_HAL_TIM_H
#define __SN8F5703_HAL_TIM_H

#include "SN8F5703.h"

/* ��ʱ��2ʱ�ӷ�Ƶ */
#define TIM2_FCPU_DIV12		((uint8_t)0x00)	/* FCPU 12��Ƶ */
#define TIM2_FCPU_DIV24		((uint8_t)0x80)	/* FCPU 24��Ƶ */

/* ��ʱ��2ʱ��Դѡ�� */
#define TIM2_CLK_FCPU			((uint8_t)0x01)	/* ʱ��ԴΪFCPU */
#define TIM2_CLK_T2				((uint8_t)0x02)	/* ʱ��ԴΪT2���� */
#define TIM2_CLK_GATE			((uint8_t)0x03)	/* ʱ��ԴΪFCPU����T2���ſ��ƶ�ʱֹͣ */

/* ��ʱ��2ʱ�ӷ�Ƶ */
#define TIM2_AUTORELOAD_PRELOAD_COUNTER	((uint8_t)0x10)	/* ͨ��������������� CRCH/CRCL ��ֵ�� TH2/TL2 */
#define TIM2_AUTORELOAD_PRELOAD_T2RL		((uint8_t)0x18)	/* ͨ�� T2RL ���ż��� CRCH/CRCL ��ֵ�� TH2/TL2 */

/* ��ʱ��2CC0������ */
#define TIM2_ICPOLARITY_RISING		((uint8_t)0x40)	/* T2CC0������ʱ��T2������������CRC�Ĵ����� */
#define TIM2_ICPOLARITY_FALLING		((uint8_t)0x00)	/* T2CC0�½���ʱ��T2������������CRC�Ĵ����� */

/* ��ʱ��2 ���벶��ͨ��ö�� */
typedef enum
{
  TIM2_IC_CHANNEL_0	= 0x01U,    /*!< The ic channel is 1	*/
  TIM2_IC_CHANNEL_1	= 0x02U,    /*!< The ic channel is 2	*/
  TIM2_IC_CHANNEL_2	= 0x04U,    /*!< The ic channel is 3	*/
  TIM2_IC_CHANNEL_3	= 0x08U,    /*!< The ic channel is 4	*/
} TIM2_IC_Channel;

/* ��ʱ��2�ṹ�� */
typedef struct
{
  uint8_t Prescaler;  
  uint8_t AutoReloadPreload;
	uint8_t ClockSource;
	uint16_t Period;
} TIM2_Base_InitTypeDef;

/* ��ʱ��2���벶��ṹ�� */
typedef struct
{
	uint8_t ICPolarity;
	uint8_t ICSelection;  
} TIM2_IC_InitTypeDef;

/* HAL��TIM2ģ��ӿں��� */
void HAL_TIM2_Base_Init(TIM2_Base_InitTypeDef* htim);
void HAL_TIM2_IC_Init(TIM2_IC_InitTypeDef* htim);
uint16_t HAL_TIM2_ReadCapturedValue(TIM2_IC_Channel Channel);

#endif

