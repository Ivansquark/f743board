#ifndef TIMER_H
#define TIMER_H

#include "stm32h743xx.h"

class GP_Timers {
public:    
    enum Period {
        us=0,
        ms=1
    };    
    
    GP_Timers(uint8_t timNum, Period period);    
    bool TimSets=0;
static GP_Timers* pThis;
private:
    void timer_ini(uint8_t tim, Period period);
};



#endif //TIMER_H