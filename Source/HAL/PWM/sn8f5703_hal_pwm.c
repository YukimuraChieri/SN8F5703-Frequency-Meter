#include "sn8f5703_hal_pwm.h"

void HAL_PWM_Init(PWM_InitTypeDef* PWM_Init)
{
    /* PWMʱ�ӷ�Ƶ���� */
    PW1M |= PWM_Init->ClockDivision;
    /* PWM�������� */
    PW1YH = PWM_Init->Period;
    /* PWMռ�ձ����� */
    PW1D = PWM_Init->Pulse;
    /* PWM1X�������� */
    switch (PWM_Init->OCPolarity_1X)
    {
        case PWM1X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_1X; break;
        case PWM1X_OCPolarity_LOW: PW1M &= ~PWM_Init->OCPolarity_1X; break;
    }
    /* PWM2X�������� */
    switch (PWM_Init->OCPolarity_2X)
    {
        case PWM2X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_1X; break;
        case PWM2X_OCPolarity_LOW: PW1M &= ~PWM_Init->OCPolarity_1X; break;
    }
    
    PW1M |= 0x80;       /* ʹ��PWM���� */
}

void HAL_PWM_Start(uint8_t Channel)
{
    PW1CH |= Channel;   /* ����PWMͨ�� */
}

void HAL_PWM_Stop(uint8_t Channel)
{
    PW1M &= ~0x80;      /* ��ֹPWM���� */
    PW1CH &= ~Channel;  /* �ر�PWMͨ�� */
}



