#ifndef __FML_SEG_H
#define __FML_SEG_H

#include "hdl_tm1628.h"

/* FML层SEG模块接口函数 */
void FML_SEG_Init(void);		/* 初始化数码管 */
void FML_SEG_Display(uint8_t dig, uint8_t seg);	/* 数码管单个显示 */
void FML_SEG_ShowNum(uint16_t num);	/* 数码管显示数字 */

#endif
