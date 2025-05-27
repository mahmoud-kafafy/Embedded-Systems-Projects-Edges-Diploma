################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hmi_app.c \
../keypad.c \
../lcd.c \
../m_gpio.c \
../uart_m.c 

OBJS += \
./hmi_app.o \
./keypad.o \
./lcd.o \
./m_gpio.o \
./uart_m.o 

C_DEPS += \
./hmi_app.d \
./keypad.d \
./lcd.d \
./m_gpio.d \
./uart_m.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


