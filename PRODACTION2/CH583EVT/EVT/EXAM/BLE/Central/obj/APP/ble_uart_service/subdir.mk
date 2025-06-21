################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/ble_uart_service/ble_uart_service.c \
../APP/ble_uart_service/ble_uart_service_16bit.c \
../APP/ble_uart_service/ble_uart_service_same_16bit_char.c \
../APP/ble_uart_service/ble_uart_service_same_char.c 

OBJS += \
./APP/ble_uart_service/ble_uart_service.o \
./APP/ble_uart_service/ble_uart_service_16bit.o \
./APP/ble_uart_service/ble_uart_service_same_16bit_char.o \
./APP/ble_uart_service/ble_uart_service_same_char.o 

C_DEPS += \
./APP/ble_uart_service/ble_uart_service.d \
./APP/ble_uart_service/ble_uart_service_16bit.d \
./APP/ble_uart_service/ble_uart_service_same_16bit_char.d \
./APP/ble_uart_service/ble_uart_service_same_char.d 


# Each subdirectory must supply rules for building sources it contributes
APP/ble_uart_service/%.o: ../APP/ble_uart_service/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCLK_OSC32K=0 -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Central\APP\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Central\Profile\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

