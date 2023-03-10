#include "sn8f5703_hal_pwm.h"

void HAL_PWM_Init(PWM_InitTypeDef* PWM_Init)
{
    /* PWM时钟分频设置 */
    PW1M |= PWM_Init->ClockDivision;
    /* PWM周期设置 */
    PW1YH = PWM_Init->Period;
    /* PWM占空比设置 */
    PW1D = PWM_Init->Pulse;
    /* PWM1X极性设置 */
    switch (PWM_Init->OCPolarity_1X)
    {
        case PWM1X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_1X; break;
        case PWM1X_OCPolarity_LOW: PW1M &= ~PWM_Init->OCPolarity_1X; break;
    }
    /* PWM2X极性设置 */
    switch (PWM_Init->OCPolarity_2X)
    {
        case PWM2X_OCPolarity_HIGH: PW1M |= PWM_Init->OCPolarity_1X; break;
        case PWM2X_OCPolarity_LOW: PW1M &= ~PWM_Init->OCPolarity_1X; break;
    }
    
    PW1M |= 0x80;       /* 使能PWM功能 */
}

void HAL_PWM_Start(uint8_t Channel)
{
    PW1CH |= Channel;   /* 开启PWM通道 */
}

void HAL_PWM_Stop(uint8_t Channel)
{
    PW1M &= ~0x80;      /* 禁止PWM功能 */
    PW1CH &= ~Channel;  /* 关闭PWM通道 */
}



