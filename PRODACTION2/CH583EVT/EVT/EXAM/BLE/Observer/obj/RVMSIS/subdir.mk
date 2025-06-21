################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Astap/Desktop/CH583EVT/EVT/EXAM/SRC/RVMSIS/core_riscv.c 

OBJS += \
./RVMSIS/core_riscv.o 

C_DEPS += \
./RVMSIS/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
RVMSIS/core_riscv.o: C:/Users/Astap/Desktop/CH583EVT/EVT/EXAM/SRC/RVMSIS/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Observer\APP\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\Observer\Profile\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\Astap\Desktop\CH583EVT\EVT\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

