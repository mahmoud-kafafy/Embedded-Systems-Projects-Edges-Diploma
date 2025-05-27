################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../app.c \
../dc_motor.c \
../lcd.c \
../lm35_sensor.c \
../m_gpio.c \
../pwm.c 

OBJS += \
./adc.o \
./app.o \
./dc_motor.o \
./lcd.o \
./lm35_sensor.o \
./m_gpio.o \
./pwm.o 

C_DEPS += \
./adc.d \
./app.d \
./dc_motor.d \
./lcd.d \
./lm35_sensor.d \
./m_gpio.d \
./pwm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


