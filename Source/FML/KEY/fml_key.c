#include "fml_key.h"

/* ��ʼ������ */
void FML_KEY_Init(void)
{
    HDL_TM1628_Init();  /* ��ʼ��TM1628 */
}

/* ����ɨ�� */
uint8_t FML_KEY_Scan(void)
{
    uint8_t ret = 0;

    return ret;
}
