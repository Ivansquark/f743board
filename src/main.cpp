/*!
 * \file main file with main function from which program is started after initialization procedure in startup.cpp
 * 
 */
#include "main.h"
//#include "rcc_init.h"
//void *__dso_handle = nullptr; // dummy "guard" that is used to identify dynamic shared objects during global destruction. (in fini in startup.cpp)
extern "C" void _exit(int i) {
    while (1);
}

int main()
{	
	RCC_INIT rcc(400);  //HSI = 64 MHz
	Encoder enc;
	Buzzer buzz;
	GP_Timers tim2(2,GP_Timers::Period::ms);
	
	//ParDac dac;
	__enable_irq();
	Nor_LCD lcd;
	Figure fig;	
	//__asm volatile ("cpsid i"); //turn off interrupts		
	//GP_Timers::pThis[0]->counter=0;
	uint16_t x = 0;
	//LCD_par lcd;
	
	while(1)
	{	
		/*	
		fig.drawRect(0,0,400,240,x++ +10050);
		fig.drawRect(400,0,800,240,x++ -10050);
		fig.drawRect(0,240,400,480,x++ +20050);
		fig.drawRect(400,240,800,480,x++ -20050);
		fig.drawVerticalLine(200,120,240,10, 0x0000);
		fig.drawVerticalLine(590,120,240,10, 0x0000);
		fig.drawHorizontalLine(200,120,400,10, 0x0000);
		fig.drawHorizontalLine(200,350,400,10, 0x0000);

		fig.drawFrame(10,10,50,50,3,0xFF00);
		fig.drawFrame(9,9,51,51,1,0xFFA0);
		fig.drawLine(800,0,0,433,0x0000);
		fig.drawFatCircle(400,240,100,5,fig.RED);
		tim2.delay_ms(500);
		*/
		lcd.writeData(x++);		
		
		if(enc.But_PC3){
			uint16_t counter=25;
			while(counter){
				if(tim2.TimSets) {  // 1 ms					
						buzz.beep();
						counter--; 
						tim2.TimSets=false;
				}				
			}
			buzz.off();
			enc.But_PC3 = 0;
		}		
	}
    return 0;
}
