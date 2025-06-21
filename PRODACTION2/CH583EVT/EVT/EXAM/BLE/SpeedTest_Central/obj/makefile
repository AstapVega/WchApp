################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SpeedTest_Central.hex \

SECONDARY_LIST += \
SpeedTest_Central.lst \

SECONDARY_SIZE += \
SpeedTest_Central.siz \


# All Target
all: SpeedTest_Central.elf secondary-outputs

# Tool invocations
SpeedTest_Central.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -L"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"SpeedTest_Central.map" --specs=nano.specs --specs=nosys.specs -o "SpeedTest_Central.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
SpeedTest_Central.hex: SpeedTest_Central.elf
	@	riscv-none-embed-objcopy -O ihex "SpeedTest_Central.elf"  "SpeedTest_Central.hex"
	@	@
SpeedTest_Central.lst: SpeedTest_Central.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "SpeedTest_Central.elf" > "SpeedTest_Central.lst"
	@	@
SpeedTest_Central.siz: SpeedTest_Central.elf
	@	riscv-none-embed-size --format=berkeley "SpeedTest_Central.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SpeedTest_Central.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
