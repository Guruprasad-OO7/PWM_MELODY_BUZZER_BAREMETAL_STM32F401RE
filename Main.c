#include "stm32f4xx.h"
#define TIMER_CLOCK_HZ 1000000
#define SYSTEM_CORE_CLOCK 16000000
typedef struct
{
    uint16_t freq;
    uint16_t duration;
} Note;
void GPIO_Init(void);
void TIM3_PWM_Init(void);
void SysTick_Init(void);
void play_note(uint16_t freq, uint16_t duration);
void delay_ms(uint32_t ms);
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_REST 0
Note melody[] = {
    {NOTE_C4,300},
    {NOTE_D4,300},
    {NOTE_E4,300},
    {NOTE_F4,300},
    {NOTE_G4,300},
    {NOTE_A4,300},
    {NOTE_B4,300},
    {NOTE_REST,300}
};
int main(void)
{
    GPIO_Init();
    TIM3_PWM_Init();
    SysTick_Init();
    while(1)
    {
        for (int i=0;i<sizeof(melody)/sizeof(Note);i++)
        {
            play_note(melody[i].freq, melody[i].duration);
            delay_ms(50);
        }

        delay_ms(1000);
    }
}
void GPIO_Init(void)
{
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &=~(3 << (6 * 2));
    GPIOA->MODER |=(2 << (6 * 2));
    GPIOA->AFR[0] &=~(0xF << (6 * 4));
    GPIOA->AFR[0] |=(2 << (6 * 4));
}
void TIM3_PWM_Init(void)
{
    RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
    TIM3->PSC =(SYSTEM_CORE_CLOCK / TIMER_CLOCK_HZ) - 1;
    TIM3->ARR =1000-1;
    TIM3->CCR1 =500;
    TIM3->CCMR1 |=(6 << 4);
    TIM3->CCMR1 |=TIM_CCMR1_OC1PE;
    TIM3->CCER |=TIM_CCER_CC1E;
    TIM3->CR1 |=TIM_CR1_ARPE;
    TIM3->EGR |=TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN;
}
void SysTick_Init(void)
{
    SysTick->LOAD =SYSTEM_CORE_CLOCK/1000-1;
    SysTick->VAL =0;
    SysTick->CTRL =SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}
void delay_ms(uint32_t ms)
{
    for (uint32_t i=0;i< ms;i++)
    {
        while (!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));
    }
}
void play_note(uint16_t freq,uint16_t duration)
{
    if (freq==0)
    {
        TIM3->CCR1=0; //Silence
    }else
    {
        uint32_t arr =TIMER_CLOCK_HZ/freq;
        TIM3->CR1 &=~TIM_CR1_CEN;// Stop timer
        TIM3->ARR =arr-1;
        TIM3->CCR1 =arr/2;// 50% duty cycle
        TIM3->EGR |=TIM_EGR_UG;
        TIM3->CR1 |=TIM_CR1_CEN;
    }
    delay_ms(duration);
}
