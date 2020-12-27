#ifndef FMC_H
#define FMC_H

#include "stm32h743xx.h"
#include "timer.h"
#include "math.h"

struct LCD_TypeDef {        
volatile uint8_t CMD;
volatile uint8_t DATA;  	
   	
};
#define LCD_BASE    ((uint32_t)(0x60000000 | 0x0000FFFF)) // A16 (0xFFFF - DATA, 0x10000 - CMD )
#define LCD         ((LCD_TypeDef *) LCD_BASE)

class Nor_LCD_interface {
public:
    Nor_LCD_interface(){}
    void writeData(uint16_t data);
    void writeCmd(uint16_t cmd);
    void writeReg(const uint16_t LCD_REG, const uint16_t cmd);
protected:
    void setColumn(uint16_t x);
    void setRow(uint16_t y);
    void setRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
private:
    inline void delay(uint32_t val) {
        while(val--){__ASM("nop");}
    } 
    
};

class Nor_LCD : public Nor_LCD_interface{
public:
    Nor_LCD();
    static Nor_LCD* pThis;
private:
    void fmc_lcd_init();
    void display_init();
    inline void res_on(){GPIOA->BSRR |= GPIO_BSRR_BS15;}
    inline void res_off(){GPIOA->BSRR |= GPIO_BSRR_BR15;}
};

class Pixel : public Nor_LCD_interface {
public: 
    enum COLOR {
        RED        =    0xf800,
        GREEN      =    0x07e0,
        BLUE       =    0x001f,
        BLACK      =    0x0000,
        YELLOW     =    0xffe0,
        WHITE      =    0xffff,
        CYAN       =    0x07ff,
        BRIGHT_RED =    0xf810,
        GRAY1      =    0x8410,
        GRAY2      =    0x4208
    };
    Pixel(){}
    void setPixel(uint16_t x, uint16_t y,uint16_t color);
};

class Rect : public Pixel {
public: 
    Rect(){}
    void drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color=Pixel::WHITE);
};
class Figure : public Rect {
public: 
    Figure();
    void drawVerticalLine(uint16_t x1, uint16_t y1, uint16_t length, uint16_t width, uint16_t color);
    void drawHorizontalLine(uint16_t x1, uint16_t y1, uint16_t length, uint16_t width, uint16_t color);
    void drawFrame(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t width, uint16_t color);
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    void drawCircle(uint16_t x,uint16_t y,float R, uint16_t color=BLACK);
    void drawFatCircle(uint16_t x,uint16_t y,float R,uint16_t width, uint16_t color=BLACK);

private:
    inline void swap(uint16_t* x1, uint16_t* x2) {
        if(*x1>*x2){uint16_t z=*x1; *x1=*x2; *x2=z;}
    }
};


#endif //FMC_H