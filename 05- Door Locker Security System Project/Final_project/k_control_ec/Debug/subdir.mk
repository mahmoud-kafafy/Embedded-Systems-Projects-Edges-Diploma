################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../control_ecu.c \
../dc_motor.c \
../external_eeprom.c \
../m_gpio.c \
../pwm.c \
../timer1.c \
../twi.c \
../uart_m.c 

OBJS += \
./buzzer.o \
./control_ecu.o \
./dc_motor.o \
./external_eeprom.o \
./m_gpio.o \
./pwm.o \
./timer1.o \
./twi.o \
./uart_m.o 

C_DEPS += \
./buzzer.d \
./control_ecu.d \
./dc_motor.d \
./external_eeprom.d \
./m_gpio.d \
./pwm.d \
./timer1.d \
./twi.d \
./uart_m.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


