################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/LCD_TEST.c \
../APP/PM_TEST.c \
../APP/TEST.c \
../APP/alex_board.c \
../APP/alex_menu.c \
../APP/app_drv_fifo.c \
../APP/ble_uart_service.c \
../APP/hlw8110.c \
../APP/large_LCD32.c \
../APP/my_FLASH.c \
../APP/peripheral.c \
../APP/peripheral_main.c \
../APP/vlad_menu.c 

OBJS += \
./APP/LCD_TEST.o \
./APP/PM_TEST.o \
./APP/TEST.o \
./APP/alex_board.o \
./APP/alex_menu.o \
./APP/app_drv_fifo.o \
./APP/ble_uart_service.o \
./APP/hlw8110.o \
./APP/large_LCD32.o \
./APP/my_FLASH.o \
./APP/peripheral.o \
./APP/peripheral_main.o \
./APP/vlad_menu.o 

C_DEPS += \
./APP/LCD_TEST.d \
./APP/PM_TEST.d \
./APP/TEST.d \
./APP/alex_board.d \
./APP/alex_menu.d \
./APP/app_drv_fifo.d \
./APP/ble_uart_service.d \
./APP/hlw8110.d \
./APP/large_LCD32.d \
./APP/my_FLASH.d \
./APP/peripheral.d \
./APP/peripheral_main.d \
./APP/vlad_menu.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Peripheral\APP\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Peripheral\Profile\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

