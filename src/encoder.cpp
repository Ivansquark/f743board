#include "encoder.h"

Encoder* Encoder::pThis = nullptr;

Encoder::Encoder() {
    encoder_init();
    pThis = this;
}

void Encoder::encoder_init() {
    //! GpioA PA3-Enc1_CW PB7-Enc1_CCW PC3_Enc1_but |  PA-8-Enc2_Cw  - PB5-Enc2_CCW PC9_Enc1_but
    //! but Enc1
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN; 
    GPIOC->MODER &=~ GPIO_MODER_MODE3;      // input mode
    GPIOC->PUPDR %=~ GPIO_PUPDR_PUPD3;      // no-pullup no-pulldown (connected to Vdd)
    
    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC; 
    EXTI->FTSR1 |= EXTI_FTSR1_TR3;
    EXTI->IMR1 |= EXTI_IMR1_IM3;
    EXTI->PR1 |= EXTI_PR1_PR3;
    NVIC_EnableIRQ(EXTI3_IRQn);
}

extern "C" void EXTI3_IRQHandler(void) {
    EXTI->PR1=EXTI_PR1_PR3;
    Encoder::pThis->But_PC3 = true;
}