#ifndef FMC_H
#define FMC_H

#include "stm32h743xx.h"

class Nor_LCD {
public:
    Nor_LCD();
    static Nor_LCD* pThis;
private:
    void lcd_init();

};


#endif //FMC_H