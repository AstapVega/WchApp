################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/app_usb.c \
../APP/buf.c \
../APP/hci_test.c \
../APP/main.c \
../APP/test_dtm.c \
../APP/uart.c 

OBJS += \
./APP/app_usb.o \
./APP/buf.o \
./APP/hci_test.o \
./APP/main.o \
./APP/test_dtm.o \
./APP/uart.o 

C_DEPS += \
./APP/app_usb.d \
./APP/buf.d \
./APP/hci_test.d \
./APP/main.d \
./APP/test_dtm.d \
./APP/uart.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DBLE_CALIBRATION_ENABLE=0 -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Direct_Test_Mode\APP\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

