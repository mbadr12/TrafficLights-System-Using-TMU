################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_program.c \
../GIE_program.c \
../PORT_program.c \
../TIMER_program.c \
../TMU_Program.c \
../main.c 

OBJS += \
./DIO_program.o \
./GIE_program.o \
./PORT_program.o \
./TIMER_program.o \
./TMU_Program.o \
./main.o 

C_DEPS += \
./DIO_program.d \
./GIE_program.d \
./PORT_program.d \
./TIMER_program.d \
./TMU_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


