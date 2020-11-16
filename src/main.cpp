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
	RCC_INIT rcc(400);
	
	Encoder enc;
	Buzzer buzz;
	GP_Timers tim2(2,GP_Timers::Period::ms);
	ParDac dac;
	__enable_irq();
	//__asm volatile ("cpsid i"); //turn off interrupts	
	int devider_counter = 100;
	while(1)
	{
		dac.set_dac127(127);
		dac.set_dac127(0);
		//GPIOE->BSRR |= GPIO_BSRR_BS0;
		//GPIOE->BSRR |= GPIO_BSRR_BR0;

		//buzz.beep();
		//for(int i=0;i<800000;i++){};
		
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
