


























.build/uno/src/sketch.o : .build/uno/src/sketch.cpp
	@echo [93msrc/sketch.cpp[0m
	@mkdir -p .build/uno/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/standard -fno-exceptions -iquote src  -o $@ -c .build/uno/src/sketch.cpp
include .build/uno/src/sketch.d







.build/uno/firmware.elf : .build/uno/src/sketch.o
	@echo [92mLinking firmware.elf[0m
	@/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build/uno/firmware.hex : .build/uno/firmware.elf
	@echo [92mConverting to firmware.hex[0m
	@/usr/share/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build/uno/src/dependencies.d

all : .build/uno/firmware.hex
	@true

