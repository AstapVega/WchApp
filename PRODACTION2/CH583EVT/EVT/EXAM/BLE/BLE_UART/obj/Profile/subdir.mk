################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/devinfoservice.c \
../Profile/gattprofile.c 

OBJS += \
./Profile/devinfoservice.o \
./Profile/gattprofile.o 

C_DEPS += \
./Profile/devinfoservice.d \
./Profile/gattprofile.d 


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCH583 -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\Profile\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\app_drv_fifo" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

