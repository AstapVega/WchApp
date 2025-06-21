################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ancs.c \
../src/main.c 

OBJS += \
./src/ancs.o \
./src/main.o 

C_DEPS += \
./src/ancs.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=0 -DHAL_KEY=1 -DCONFIG_RISCV -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\services" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\src" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -isystem"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\includes" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

