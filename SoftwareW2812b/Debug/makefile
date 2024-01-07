################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/Peripheral_Drivers/ws2812b/subdir.mk
-include Core/Src/Example/ws2812b/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SoftwareW2812.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SoftwareW2812.list \

OBJCOPY_HEX += \
SoftwareW2812.hex \

OBJCOPY_BIN += \
SoftwareW2812.bin \


# All Target
all: SoftwareW2812.elf secondary-outputs

# Tool invocations
SoftwareW2812.elf: $(OBJS) $(USER_OBJS) C:\Users\Nguyet\STM32CubeIDE\workspace_1.3.0\STM32MCU_KIT2\SoftwareW2812b\STM32F103RBTX_FLASH.ld
	arm-none-eabi-gcc -o "SoftwareW2812.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Nguyet\STM32CubeIDE\workspace_1.3.0\STM32MCU_KIT2\SoftwareW2812b\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SoftwareW2812.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SoftwareW2812.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SoftwareW2812.list"
	@echo 'Finished building: $@'
	@echo ' '

SoftwareW2812.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "SoftwareW2812.hex"
	@echo 'Finished building: $@'
	@echo ' '

SoftwareW2812.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SoftwareW2812.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
