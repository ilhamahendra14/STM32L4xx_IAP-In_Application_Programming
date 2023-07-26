################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/astrocast/astronode_application.c \
../Core/astrocast/astronode_transport.c 

OBJS += \
./Core/astrocast/astronode_application.o \
./Core/astrocast/astronode_transport.o 

C_DEPS += \
./Core/astrocast/astronode_application.d \
./Core/astrocast/astronode_transport.d 


# Each subdirectory must supply rules for building sources it contributes
Core/astrocast/%.o Core/astrocast/%.su: ../Core/astrocast/%.c Core/astrocast/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/1. Avirlink_S2/4. Firmware - STM32Cube IDE/Avirlink S2 - Water Quality - IAP/Core/astrocast" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-astrocast

clean-Core-2f-astrocast:
	-$(RM) ./Core/astrocast/astronode_application.d ./Core/astrocast/astronode_application.o ./Core/astrocast/astronode_application.su ./Core/astrocast/astronode_transport.d ./Core/astrocast/astronode_transport.o ./Core/astrocast/astronode_transport.su

.PHONY: clean-Core-2f-astrocast

