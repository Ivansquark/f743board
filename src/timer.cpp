#include "timer.h"

GP_Timers* GP_Timers::pThis = nullptr;

GP_Timers::GP_Timers(uint8_t timNum = 2, Period period = ms) {
    timer_ini(timNum, period);
    pThis = this;
}    

void GP_Timers::timer_ini(uint8_t tim, Period period) {
    switch(tim)
    {
        case 2: {
            RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
            switch (period) {
                case us:
                TIM2->PSC = 24;// TIM clk = 240000000  (clk APB1*2) => 10 MHz
                TIM2->ARR = 10-1; //1 us                
                break;
                case ms:
                TIM2->PSC = 240;// TIM clk = 240000000  (clk APB1*2) => 1 MHz
                TIM2->ARR = 1000-1; //1 ms                
                break;
            }                
            TIM2->DIER|=TIM_DIER_UIE; //interrupt at overload 
            TIM2->CR1|=TIM_CR1_CEN;
            NVIC_EnableIRQ(TIM2_IRQn); //irq enable
        }
        break;            
        default:break;
    }        
}

extern "C" void TIM2_IRQHandler(void) {
    TIM2->SR&=~TIM_SR_UIF; //drop Update interrupt flag
    GP_Timers::pThis->TimSets=true;
}