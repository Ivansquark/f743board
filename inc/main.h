#ifndef MAIN_H_
#define MAIN_H_

#include "stm32h743xx.h"
//#include "led.h"
//#include "usart1.h"
#include "core_cm7.h"
//#include "modbus.h"
//#include "timer3.h"
//#include "spilcd.h"
//#include "irq.h"
//#include "frwrapper.h"
//#include "frclasses.h"
//#include "adc.h"
//#include "button.h"
#include <stdint.h>

//***************************************************
#include "rcc_init.h"
#include "encoder.h"
#include "buzzer.h"
#include "timer.h"
#include "pardac.h"
#include "fmc.h"
//#include "lcd_par.h"
#include "watchdog.h"
#include "font.h"
#include "rtc.h"
//*******************************************************

//class SYStick
//{
//public:
//	SYStick()
//	{					
//		SysTickConfig();
//		
//	}
//	void delay_ms(__IO uint32_t milisec) 
//	{    	
//    	uint32_t start = ticks_delay;
//		while((ticks_delay - start) < milisec);
//    	//SysTick->LOAD &= ~(SysTick_CTRL_ENABLE_Msk);    // disable SysTick
//	}	
//	volatile static uint32_t ticks_delay;	
//		
//private:
//	void SysTickConfig()
//	{
//			if (SysTick_Config(72000)) // set 1ms
//    	{
//    	    while(1); // error
//    	}
//	}		
//	//static __IO uint32_t s_timer;	
//};

//volatile uint32_t SYStick::ticks_delay=0;
//
//extern "C" void SysTick_Handler(void) //обработчик прерывания системного таймера
//{
//    SYStick::ticks_delay++;
//} 
////********************************************************************

#endif //MAIN_H
