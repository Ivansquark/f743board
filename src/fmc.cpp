#include "fmc.h"

Nor_LCD* Nor_LCD::pThis = nullptr;

Nor_LCD::Nor_LCD() {
    lcd_init();
    pThis = this;
}

void Nor_LCD::lcd_init() {
    // GPIOS Enable: 
    //! D11 - FMC-A16(RS - D/C)  D14-FMC-D0  D15-FMC-D1
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN; //0x60000000 - D  0x60000001 - C
    GPIOD->MODER |= (GPIO_MODER_MODE11_1 | GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1); 
    GPIOD->MODER &=~ (GPIO_MODER_MODE11_0 | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE15_0); 
    GPIOD->OSPEEDR |= (GPIO_OSPEEDR_OSPEED11 | GPIO_OSPEEDR_OSPEED14 | GPIO_OSPEEDR_OSPEED15);
    GPIOD->AFR[1] |= ((12<<12)|(12<<24)|(12<<28));
    //! D0-FMC_D2, D1-FMC_D3, D4-FMC_NOE REED_EN, D5-FMC_NWE Write_EN, D7-FMC_NE1 (CS), D2-TS, D3-PEN
    GPIOD->MODER |= (GPIO_MODER_MODE0_1 | GPIO_MODER_MODE1_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1 | GPIO_MODER_MODE7_1);
    GPIOD->MODER &=~ (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE7_0); 
    GPIOD->OSPEEDR |= (GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED1 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED7);
    GPIOD->AFR[0] |= ((12<<0) | (12<<4) | (12<<16) | (12<<20) | (12<<28));
    GPIOD->MODER |= (GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
    GPIOD->MODER &=~ (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1); 
    GPIOD->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3);
    //! E7-FMC_D4, E8-FMC_D4, E9-FMC_D4, E10-FMC_D4,
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
    GPIOE->MODER |= (GPIO_MODER_MODE7_1 | GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1);
    GPIOE->MODER &=~ (GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0 | GPIO_MODER_MODE10_0); 
    GPIOE->OSPEEDR |= (GPIO_OSPEEDR_OSPEED7 | GPIO_OSPEEDR_OSPEED8 | GPIO_OSPEEDR_OSPEED9 | GPIO_OSPEEDR_OSPEED10);
    GPIOD->AFR[0] |= (12<<28);
    GPIOD->AFR[1] |= ((12<<0)|(12<<4)|(12<<8));
    //! A-15 RES LCD
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODE15_0);
    GPIOA->MODER &=~ (GPIO_MODER_MODE15_1); 
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED15);
    //! HCLK3 clock source
    RCC->D1CCIPR &=~ RCC_D1CCIPR_FMCSEL;
    //! FMC clock enable
    RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;    
}