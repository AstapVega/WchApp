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
SYNC_SCAN.hex \

SECONDARY_LIST += \
SYNC_SCAN.lst \

SECONDARY_SIZE += \
SYNC_SCAN.siz \


# All Target
all: SYNC_SCAN.elf secondary-outputs

# Tool invocations
SYNC_SCAN.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -L"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"SYNC_SCAN.map" --specs=nano.specs --specs=nosys.specs -o "SYNC_SCAN.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
SYNC_SCAN.hex: SYNC_SCAN.elf
	@	riscv-none-embed-objcopy -O ihex "SYNC_SCAN.elf"  "SYNC_SCAN.hex"
	@	@
SYNC_SCAN.lst: SYNC_SCAN.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "SYNC_SCAN.elf" > "SYNC_SCAN.lst"
	@	@
SYNC_SCAN.siz: SYNC_SCAN.elf
	@	riscv-none-embed-size --format=berkeley "SYNC_SCAN.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SYNC_SCAN.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
