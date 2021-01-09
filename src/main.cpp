/*!
 * \file main file with main function from which program is started after initialization procedure in startup.cpp
 * 
 */
#define __cplusplus 2017

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
#include "sd.h"
#include "normalqueue.h"
//*******************************************************


#include "main.h"
//#include "rcc_init.h"
//void *__dso_handle = nullptr; // dummy "guard" that is used to identify dynamic shared objects during global destruction. (in fini in startup.cpp)
extern "C" void _exit(int i) {
    while (1);
}

#include "stdlib.h"
#define Pi 3.1415926535F

uint8_t arr1[512]={0};
uint8_t arr2[512]={0};
uint8_t arr3[512]={0};
void Error_Handler(void){}
int main()
{
	
	Rtc rtc;
	RCC_INIT rcc(400);  // realy 360 MHz
	
	Buzzer buzz;
	Independed_WatchDog watchDog(0x4FF);
	GP_Timers tim2(2,GP_Timers::Period::ms);
	GP_Timers tim3_watchDog(3,GP_Timers::Period::ms);
	GP_Timers tim4_encoders(4,GP_Timers::Period::us); //encoders timer 100 us
	
	//ParDac dac;
	__enable_irq();
	Nor_LCD lcd;
	Figure fig;	
	//__asm volatile ("cpsid i"); //turn off interrupts		
	//GP_Timers::pThis[0]->counter=0;
	uint32_t x = 0;
	srand ( x );
	fig.drawRect(0,0,800,480,fig.CYAN);	
  	
	
	fig.drawFatCircle(400,240,150,50,fig.YELLOW);
	Font_28x30_D font_28x30(fig.CYAN,fig.BLACK);
	font_28x30.drawString(100,0,"1234567890");
	Font_28x30_D font1_28x30(fig.YELLOW,fig.BLUE);
	font1_28x30.setColors(fig.CYAN, fig.BRIGHT_RED);
	
	SD sd;
	Encoder enc;
	font1_28x30.drawIntValue(0,00,font1_28x30.intToChar(sd.SDCard.Type),1);
	font1_28x30.drawIntValue(0,35,font1_28x30.intToChar(sd.SDCard.Capacity),1);
	font1_28x30.drawIntValue(0,70,font1_28x30.intToChar(sd.SDCard.BlockCount),1);
	
	//font1_28x30.drawIntValue(0,350,font1_28x30.intToChar(sd.SDCard.SCR[1]),1);
	uint8_t arr[512]={0};
	for(int i=0; i<512; i++) {
		arr[i] = i+10;
	}
	
	// addr = 512/4=128-address_in_uint32_t    128*100 - address of block number 100
	//sd.WriteBlock(0,(uint32_t*)arr,512);  
	//sd.EraseBlock(0,61056);  
	sd.ReadBlock(0,(uint32_t*)arr1,512);
	sd.ReadBlock(1,(uint32_t*)arr2,512);
	sd.ReadBlock(512,(uint32_t*)arr3,512);
	NormalQueue8 que; //128*8 SIZE queue
	
	while(1)
	{	
		x++;
		
		
		font1_28x30.drawIntValue(0,440,font1_28x30.intToChar(x),7);  // counter
		//
		//font1_28x30.drawIntValue(300,440,font1_28x30.intToChar(enc.enc1_counter),3);
		//font1_28x30.drawIntValue(500,440,font1_28x30.intToChar(enc.enc2_counter),3);
		//font1_28x30.drawIntValue(700,440,font1_28x30.intToChar(enc.enc_counter),3);
		//fig.drawFilledTriangle((rand() % 800),(rand() % 480),
		//					   (rand() % 800),(rand() % 480),
		//					   (rand() % 800),(rand() % 480), (uint16_t)(rand() % 0xFFFF));
		//fig.drawRect((rand() % 800),(rand() % 480),(rand() % 800),(rand() % 480), (rand() % 0xFFFF));
		
		
		//tim2.delay_ms(2500);
		
		//lcd.writeData(x++);		
		if(enc.But_PA3){			
			if(enc.enc_counter!=0) {
				enc.enc_counter--;
			} else {enc.enc_counter=360;}
			fig.drawFatLineOnCircle(400,240,150,enc.enc_counter+5,5,40,fig.YELLOW);
			fig.drawFatLineOnCircle(400,240,150,enc.enc_counter,5,40,fig.RED);
			//enc.SM_backward(10);
			enc.But_PA3 = 0;
		}			
		if(enc.But_PB5){
			if(enc.enc_counter!=360) {
				enc.enc_counter++;
			} else {enc.enc_counter=0;}
			fig.drawFatLineOnCircle(400,240,150,enc.enc_counter,5,40,fig.YELLOW);
			fig.drawFatLineOnCircle(400,240,150,enc.enc_counter+5,5,40,fig.RED);
			//enc.SM_forward(10);
			enc.But_PB5 = false;
		}
		if(enc.But_PC9){
			uint16_t counter=5;
			while(counter){
				if(tim2.TimSets) {  // 1 ms					
						buzz.beep();
						counter--; 
						tim2.TimSets=false;
				}				
			}
			buzz.off();
			enc.But_PC9 = false;
		}
		//watchDog.refreshCounter(); // resets in counter
// show time:		
		//rtc.getTime();
		//font1_28x30.drawIntValue(500,0,font1_28x30.intToChar(rtc.currentTime.hour/10),1);
		//font1_28x30.drawIntValue(528,0,font1_28x30.intToChar(rtc.currentTime.hour%10),1);
		//font1_28x30.drawSymbol(554,0,':');
		//font1_28x30.drawIntValue(582,0,font1_28x30.intToChar(rtc.currentTime.minute/10),1);
		//font1_28x30.drawIntValue(610,0,font1_28x30.intToChar(rtc.currentTime.minute%10),1);
		//font1_28x30.drawSymbol(638,0,':');
		//font1_28x30.drawIntValue(666,0,font1_28x30.intToChar(rtc.currentTime.second/10),1);
		//font1_28x30.drawIntValue(694,0,font1_28x30.intToChar(rtc.currentTime.second%10),1);
		//rtc.getDate();
		//font1_28x30.drawIntValue(500,40,font1_28x30.intToChar(rtc.currentDate.day/10),1);
		//font1_28x30.drawIntValue(528,40,font1_28x30.intToChar(rtc.currentDate.day%10),1);
		//font1_28x30.drawSymbol(554,40,'.');
		//font1_28x30.drawIntValue(582,40,font1_28x30.intToChar(rtc.currentDate.month/10),1);
		//font1_28x30.drawIntValue(610,40,font1_28x30.intToChar(rtc.currentDate.month%10),1);
		//font1_28x30.drawSymbol(638,40,'.');
		//font1_28x30.drawIntValue(666,40,font1_28x30.intToChar(rtc.currentDate.year/10),1);
		//font1_28x30.drawIntValue(694,40,font1_28x30.intToChar(rtc.currentDate.year%10),1);
	}
	

    return 0;
}



