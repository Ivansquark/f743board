.PHONY: all,clean,load

CC = arm-none-eabi-gcc
OBJC = arm-none-eabi-objcopy
OBJD = arm-none-eabi-objdump
AS = arm-none-eabi-as
LD = arm-none-eabi-ld

INC = inc/
LIB = lib/
BLD = build/
SRC = src/
#FRS = freeRTOS/src/
#FRH = freeRTOS/inc/

CPPFLAGS = -mthumb -mcpu=cortex-m7 -c -g -O0 -Wall \
	-mfpu=fpv5-d16 -mfloat-abi=hard -fno-exceptions \
	-fno-math-errno -ffunction-sections -fdata-sections -u_printf_float \
	-fno-rtti --specs=nosys.specs --specs=nano.specs -fno-common -D"assert_param(x)=" \
	-L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\lib\gcc\arm-none-eabi\9.3.1\thumb\v7e-m+dp\hard" 
	#
	#-L"C:/Program Files (x86)/GNUArmEmbeddedToolchain/9_2020-q2-update/arm-none-eabi/"	
	#-L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\lib\gcc\arm-none-eabi\9.3.1" \
	 
LCPPFLAGS = -mcpu=cortex-m7 -march=armv7e-m -mthumb -g -nostartfiles -lm -lc -lstdc++ \
		 -mfloat-abi=hard  -mfpu=fpv5-d16 -specs=nosys.specs -specs=nano.specs \
		 -fno-use-cxa-atexit -Xlinker -Map=$(BLD)main.map \
		 -L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\arm-none-eabi\lib\thumb\v7e-m+dp\hard" \
		 -L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\lib\gcc\arm-none-eabi\9.3.1\thumb\v7e-m+dp\hard"
		 #-L"C:/Program Files (x86)/GNUArmEmbeddedToolchain/9_2020-q2-update/arm-none-eabi/" \
		 -L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\lib\gcc\arm-none-eabi\9.3.1" \
		 -L"C:\Program Files (x86)\GNUArmEmbeddedToolchain\9_2020-q2-update\arm-none-eabi\lib" \
		 #-z muldefs  -u_printf_float 

load: $(BLD)main.bin
	openocd -f lib/stlink.cfg -f lib/stm32h7x.cfg -c "program $(BLD)main.bin verify reset exit 0x08000000"
	
all: $(BLD)main.bin $(BLD)main.elf $(BLD)main.lst
$(BLD)main.bin: $(BLD)main.elf
	$(OBJC) $(BLD)main.elf $(BLD)main.bin -O binary

$(BLD)main.lst: $(BLD)main.elf
	$(OBJD) -D $(BLD)main.elf > $(BLD)main.lst

$(BLD)main.elf: $(BLD)startup.o $(BLD)main.o $(BLD)timer.o $(BLD)encoder.o $(BLD)rcc_init.o $(BLD)pardac.o $(BLD)fmc.o $(BLD)font.o $(BLD)F_28x30_Digit.o $(BLD)rtc.o
 
	$(CC) -o $(BLD)main.elf -T$(LIB)stm32h743.ld \
	$(BLD)startup.o $(BLD)timer.o $(BLD)encoder.o $(BLD)main.o $(BLD)rcc_init.o \
	$(BLD)pardac.o $(BLD)fmc.o $(BLD)font.o $(BLD)F_28x30_Digit.o $(BLD)rtc.o \
	-I$(LIB) $(LCPPFLAGS)

# malloc.o tasks.o heap_2.o timers.o list.o port.o queue.o \
	
	arm-none-eabi-objcopy -j .text -j .data -j .bss -O ihex $(BLD)main.elf $(BLD)main.hex  
	arm-none-eabi-size $(BLD)main.elf
$(BLD)startup.o: $(LIB)startup.cpp
	$(CC) $(LIB)startup.cpp -o $(BLD)startup.o $(CPPFLAGS)
#malloc.o: src/malloc.cpp
#	$(CC) src/malloc.cpp -o malloc.o -I$(INC) -I$(FRH) $(CPPFLAGS)
	
#port.o: freeRTOS/src/port.c 
#	$(CC) freeRTOS/src/port.c -o port.o -I$(FRH) -I$(INC) $(CFLAGS)
#tasks.o: freeRTOS/src/tasks.c
#	$(CC) freeRTOS/src/tasks.c -o tasks.o -I$(FRH) -I$(INC) $(CFLAGS)
#queue.o: freeRTOS/src/queue.c
#	$(CC) freeRTOS/src/queue.c -o queue.o -I$(FRH) -I$(INC) $(CFLAGS)	
#list.o: freeRTOS/src/list.c
#	$(CC) freeRTOS/src/list.c -o list.o -I$(FRH) -I$(INC) $(CFLAGS)	
#timers.o: freeRTOS/src/timers.c
#	$(CC) freeRTOS/src/timers.c -o timers.o -I$(FRH) -I$(INC) $(CFLAGS)	
#heap_2.o: freeRTOS/src/heap_2.c $(INC)
#	$(CC) freeRTOS/src/heap_2.c -o heap_2.o -I$(FRH) -I$(INC) $(CFLAGS)	

$(BLD)timer.o: $(SRC)timer.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)timer.cpp -o $(BLD)timer.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)rcc_init.o: $(SRC)rcc_init.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)rcc_init.cpp -o $(BLD)rcc_init.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)encoder.o: $(SRC)encoder.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)encoder.cpp -o $(BLD)encoder.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)pardac.o: $(SRC)pardac.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)pardac.cpp -o $(BLD)pardac.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)fmc.o: $(SRC)fmc.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)fmc.cpp -o $(BLD)fmc.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)rtc.o: $(SRC)rtc.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)rtc.cpp -o $(BLD)rtc.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)	
#$(BLD)lcd_par.o: $(SRC)lcd_par.cpp #$(INC) #$(FRH)
#	$(CC) $(SRC)lcd_par.cpp -o $(BLD)lcd_par.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)	
$(BLD)font.o: $(SRC)font.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)font.cpp -o $(BLD)font.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
$(BLD)F_28x30_Digit.o: $(SRC)F_28x30_Digit.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)F_28x30_Digit.cpp -o $(BLD)F_28x30_Digit.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)				

$(BLD)main.o: $(SRC)main.cpp #$(INC) #$(FRH)
	$(CC) $(SRC)main.cpp -o $(BLD)main.o -I$(INC) -I$(LIB) -I$(FRH) $(CPPFLAGS)
	
clean:
	rm -rf $(BLD)*.o $(BLD)*.elf $(BLD)*.lst $(BLD)*.bin $(BLD)*.map $(BLD)*.hex 


	
