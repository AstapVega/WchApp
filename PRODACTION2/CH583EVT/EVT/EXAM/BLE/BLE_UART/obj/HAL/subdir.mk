################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/MCU.c \
C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/RTC.c \
C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/SLEEP.c 

OBJS += \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/MCU.o: C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/MCU.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCH583 -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\Profile\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\app_drv_fifo" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/RTC.o: C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/RTC.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCH583 -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\Profile\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\app_drv_fifo" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/SLEEP.o: C:/Users/Astap/Desktop/PRODACTION2/CH583EVT/EVT/EXAM/BLE/HAL/SLEEP.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -DCH583 -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\Profile\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\app_drv_fifo" -I"C:\Users\Astap\Desktop\PRODACTION2\CH583EVT\EVT\EXAM\BLE\BLE_UART\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

