#ifndef FMC_H
#define FMC_H

#include "stm32h743xx.h"

struct LCD_TypeDef {                             		// Структура адресуется по порядку. Базовый адрес в начале. 
	volatile uint8_t DATA;   	// 0x6001FFFE  >> 1 = 0x0000FFFF bit 16 = 0 т.е. DATA
	volatile uint8_t CMD;   	// 0x6001FFFE + 2 (т.к. uint16) = 0x60020000 >> 1 = 0x00010000 bit 16 = 1 т.е. CMD
};
#define LCD_BASE    ((uint32_t)(0x60000000 | 0x0000FFFF)) // A16 (0xFFFF - DATA, 0x10000 - CMD )
#define LCD         ((LCD_TypeDef *) LCD_BASE)

class Nor_LCD {
public:
    Nor_LCD();
    static Nor_LCD* pThis;
private:
    void lcd_init();

};


#endif //FMC_H