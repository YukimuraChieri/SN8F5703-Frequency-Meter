#ifndef __SN8F5703_HAL_TIM_H
#define __SN8F5703_HAL_TIM_H

#include "SN8F5703.h"

/* 定时器2时钟分频 */
#define TIM2_FCPU_DIV12		((uint8_t)0x00)	/* FCPU 12分频 */
#define TIM2_FCPU_DIV24		((uint8_t)0x80)	/* FCPU 24分频 */

/* 定时器2时钟源选择 */
#define TIM2_CLK_FCPU			((uint8_t)0x01)	/* 时钟源为FCPU */
#define TIM2_CLK_T2				((uint8_t)0x02)	/* 时钟源为T2引脚 */
#define TIM2_CLK_GATE			((uint8_t)0x03)	/* 时钟源为FCPU，带T2引脚控制定时停止 */

/* 定时器2时钟分频 */
#define TIM2_AUTORELOAD_PRELOAD_COUNTER	((uint8_t)0x10)	/* 通过计数器溢出加载 CRCH/CRCL 的值到 TH2/TL2 */
#define TIM2_AUTORELOAD_PRELOAD_T2RL		((uint8_t)0x18)	/* 通过 T2RL 引脚加载 CRCH/CRCL 的值到 TH2/TL2 */

/* 定时器2CC0捕获极性 */
#define TIM2_ICPOLARITY_RISING		((uint8_t)0x40)	/* T2CC0上升沿时，T2的内容锁存在CRC寄存器中 */
#define TIM2_ICPOLARITY_FALLING		((uint8_t)0x00)	/* T2CC0下降沿时，T2的内容锁存在CRC寄存器中 */

/* 定时器2 输入捕获通道枚举 */
typedef enum
{
  TIM2_IC_CHANNEL_0	= 0x01U,    /*!< The ic channel is 1	*/
  TIM2_IC_CHANNEL_1	= 0x02U,    /*!< The ic channel is 2	*/
  TIM2_IC_CHANNEL_2	= 0x04U,    /*!< The ic channel is 3	*/
  TIM2_IC_CHANNEL_3	= 0x08U,    /*!< The ic channel is 4	*/
} TIM2_IC_Channel;

/* 定时器2结构体 */
typedef struct
{
  uint8_t Prescaler;  
  uint8_t AutoReloadPreload;
	uint8_t ClockSource;
	uint16_t Period;
} TIM2_Base_InitTypeDef;

/* 定时器2输入捕获结构体 */
typedef struct
{
	uint8_t ICPolarity;
	uint8_t ICSelection;  
} TIM2_IC_InitTypeDef;

/* HAL层TIM2模块接口函数 */
void HAL_TIM2_Base_Init(TIM2_Base_InitTypeDef* htim);
void HAL_TIM2_IC_Init(TIM2_IC_InitTypeDef* htim);
uint16_t HAL_TIM2_ReadCapturedValue(TIM2_IC_Channel Channel);

#endif

