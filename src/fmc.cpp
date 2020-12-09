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
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_ASYNCWAIT; // Wait signal during asynchronous transfers
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_BURSTEN;   // Burst enable bit
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_CBURSTRW;  // write 0 - async 1 - sycnc
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_CPSIZE;    // CRAM Page Size
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_EXTMOD;    // 1: values inside FMC_BWTR register are taken into account 0: NO BWTR
    FMC_Bank1_R->BTCR[0] |= FMC_BCRx_FACCEN;     // Flash access enable  (for LCD)
    FMC_Bank1_R->BTCR[0] |= FMC_BCRx_MBKEN;      // Memory bank enable bit
    FMC_Bank1_R->BTCR[0] |= FMC_BCRx_MTYP_1;     // 0 = SRAM 1 = CRAM 2 = NOR
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_MTYP_0;    // 0 = SRAM 1 = CRAM 2 = NOR
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_MUXEN;     // Multiplexing Address/Data
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_MWID;      // 00 = 8b 01 = 16b 10 = 32bits
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_WAITCFG;   //Wait timing configuration. 0: NWAIT before wait state 1: active during wait state
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_WAITEN;    // wait enable
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCRx_WAITPOL;   // Wait signal polarity bit. 0: NWAIT active low. 1: NWAIT active high
    FMC_Bank1_R->BTCR[0] |= FMC_BCRx_WREN;       // Write enable bit
    FMC_Bank1_R->BTCR[0] &=~ FMC_BCR1_CCLKEN;    // Continious clock enable
    FMC_Bank1_R->BTCR[0] |= FMC_BCR1_FMCEN;      // FMC enable

    FMC_Bank1_R->BTCR[1] &=~ FMC_BTRx_ACCMOD;    // Access mode 0 = A, !!! 1=B !!!  , 2 = C, 3 = D Use w/EXTMOD bit
    FMC_Bank1_R->BTCR[1] &=~ FMC_BTRx_ADDHLD;   // Address-hold phase duration 1..F * 2 * HCLK
    FMC_Bank1_R->BTCR[1] &=~ FMC_BTRx_ADDSET;   // Address setup phase duration 0..F * HCLK
    FMC_Bank1_R->BTCR[1] &=~ FMC_BTRx_BUSTURN;  // Bus turnaround phase duration 0...F
    FMC_Bank1_R->BTCR[1] |= FMC_BTRx_CLKDIV_0;   // 0000: Reserved  0001:FMC_CLK period = 2 × fmc_ker_ck periods
    FMC_Bank1_R->BTCR[1] |= FMC_BTRx_DATAST_0;    //Data-phase duration 0: Reserved  01: DATAST phase duration = 1 × fmc_ker_ck clock cycles
    FMC_Bank1_R->BTCR[1] &=~ FMC_BTRx_DATLAT;    // Data latency for synchronous NOR Flash memory 0(2CK)...F(17CK)
}