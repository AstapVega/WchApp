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
-include Profile/subdir.mk
-include HAL/subdir.mk
-include APP/ble_uart_service/subdir.mk
-include APP/app_drv_fifo/subdir.mk
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
BLE_UART_PRODACT2.hex \

SECONDARY_LIST += \
BLE_UART_PRODACT2.lst \

SECONDARY_SIZE += \
BLE_UART_PRODACT2.siz \


# All Target
all: BLE_UART_PRODACT2.elf secondary-outputs

# Tool invocations
BLE_UART_PRODACT2.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L../ -L"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\LIB" -L"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"BLE_UART_PRODACT2.map" --specs=nano.specs --specs=nosys.specs -o "BLE_UART_PRODACT2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
BLE_UART_PRODACT2.hex: BLE_UART_PRODACT2.elf
	@	riscv-none-embed-objcopy -O ihex "BLE_UART_PRODACT2.elf"  "BLE_UART_PRODACT2.hex"
	@	@
BLE_UART_PRODACT2.lst: BLE_UART_PRODACT2.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "BLE_UART_PRODACT2.elf" > "BLE_UART_PRODACT2.lst"
	@	@
BLE_UART_PRODACT2.siz: BLE_UART_PRODACT2.elf
	@	riscv-none-embed-size --format=berkeley "BLE_UART_PRODACT2.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BLE_UART_PRODACT2.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
