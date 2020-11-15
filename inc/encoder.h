#ifndef ENCODER_H
#define ENCODER_H

#include "stm32h743xx.h"

class Encoder {
public: 
    Encoder();
    static Encoder* pThis;
    bool But_PC3=false;
private:
    void encoder_init();
};


#endif //ENCODER_H