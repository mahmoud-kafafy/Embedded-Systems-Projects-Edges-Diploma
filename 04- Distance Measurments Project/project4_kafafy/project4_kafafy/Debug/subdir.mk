################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application.c \
../lcd.c \
../m_gpio.c \
../m_icu.c \
../ultrasonic.c 

OBJS += \
./application.o \
./lcd.o \
./m_gpio.o \
./m_icu.o \
./ultrasonic.o 

C_DEPS += \
./application.d \
./lcd.d \
./m_gpio.d \
./m_icu.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


