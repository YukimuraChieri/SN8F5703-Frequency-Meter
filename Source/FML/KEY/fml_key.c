#include "fml_key.h"

/* 初始化按键 */
void FML_KEY_Init(void)
{
    HDL_TM1628_Init();  /* 初始化TM1628 */
}

/* 按键扫描 */
uint8_t FML_KEY_Scan(void)
{
    uint8_t ret = 0;

    return ret;
}
