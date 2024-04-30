################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/buzzer.c \
../MCAL/dcMotor.c \
../MCAL/external_eeprom.c \
../MCAL/lcd.c 

OBJS += \
./MCAL/buzzer.o \
./MCAL/dcMotor.o \
./MCAL/external_eeprom.o \
./MCAL/lcd.o 

C_DEPS += \
./MCAL/buzzer.d \
./MCAL/dcMotor.d \
./MCAL/external_eeprom.d \
./MCAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


