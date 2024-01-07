################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Peripheral_Drivers/ws2812b/ws2812b.c 

OBJS += \
./Core/Src/Peripheral_Drivers/ws2812b/ws2812b.o 

C_DEPS += \
./Core/Src/Peripheral_Drivers/ws2812b/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Peripheral_Drivers/ws2812b/ws2812b.o: ../Core/Src/Peripheral_Drivers/ws2812b/ws2812b.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I"C:/Users/Nguyet/STM32CubeIDE/workspace_1.3.0/STM32MCU_KIT2/SoftwareW2812b/Core/Inc/Example/ws2812b" -I"C:/Users/Nguyet/STM32CubeIDE/workspace_1.3.0/STM32MCU_KIT2/SoftwareW2812b/Core/Inc/Peripheral_Drivers/ws2812b" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Peripheral_Drivers/ws2812b/ws2812b.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

