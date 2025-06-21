################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/ancs_app_attr_get.c \
../services/ancs_attr_parser.c \
../services/ancs_client.c \
../services/devinfoservice.c 

OBJS += \
./services/ancs_app_attr_get.o \
./services/ancs_attr_parser.o \
./services/ancs_client.o \
./services/devinfoservice.o 

C_DEPS += \
./services/ancs_app_attr_get.d \
./services/ancs_attr_parser.d \
./services/ancs_client.d \
./services/devinfoservice.d 


# Each subdirectory must supply rules for building sources it contributes
services/%.o: ../services/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=0 -DHAL_KEY=1 -DCONFIG_RISCV -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\services" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\src" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -isystem"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\peripheral_ancs_client\includes" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

