###############################################################################
# Makefile for the project Project_RF24L01
###############################################################################

## General Flags
PROJECT = Project_RF24L01
MCU = atmega8
TARGET = Project_RF24L01.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                         -DF_CPU=8000000UL -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Project_RF24L01.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"H:\Demo\RF24L01\Versions\Demo_nRF24L01_V3_0_ZeYao\Demo_nRF24L01_V3_0_ZeYao\Demo_RF24L01_AvrMega8\Demo_RF24L01_AvrMega8\Project_RF24L01\Source_Files\app\inc" -I"H:\Demo\RF24L01\Versions\Demo_nRF24L01_V3_0_ZeYao\Demo_nRF24L01_V3_0_ZeYao\Demo_RF24L01_AvrMega8\Demo_RF24L01_AvrMega8\Project_RF24L01\Source_Files\drv_mcu\inc" -I"H:\Demo\RF24L01\Versions\Demo_nRF24L01_V3_0_ZeYao\Demo_nRF24L01_V3_0_ZeYao\Demo_RF24L01_AvrMega8\Demo_RF24L01_AvrMega8\Project_RF24L01\Source_Files\drv_periph\inc" -I"H:\Demo\RF24L01\Versions\Demo_nRF24L01_V3_0_ZeYao\Demo_nRF24L01_V3_0_ZeYao\Demo_RF24L01_AvrMega8\Demo_RF24L01_AvrMega8\Project_RF24L01\..\..\..\..\..\..\usrsoft\icc7\avr\include\avr" 

## Objects that must be built in order to link
OBJECTS = main.o drv_led.o drv_button.o drv_delay.o drv_spi.o drv_uart.o drv_RF24L01.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Project_RF24L01.hex Project_RF24L01.eep Project_RF24L01.lss size

## Compile
main.o: ../Source_Files/app/src/main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_led.o: ../Source_Files/drv_mcu/src/drv_led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_button.o: ../Source_Files/drv_mcu/src/drv_button.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_delay.o: ../Source_Files/drv_mcu/src/drv_delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_spi.o: ../Source_Files/drv_mcu/src/drv_spi.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_uart.o: ../Source_Files/drv_mcu/src/drv_uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

drv_RF24L01.o: ../Source_Files/drv_periph/src/drv_RF24L01.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Project_RF24L01.elf dep/* Project_RF24L01.hex Project_RF24L01.eep Project_RF24L01.lss Project_RF24L01.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

