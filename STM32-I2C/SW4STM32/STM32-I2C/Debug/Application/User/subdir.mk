################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/LIS2DH.c \
/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/gpio.c \
/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/i2c.c \
/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/main.c \
/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/stm32l4xx_hal_msp.c \
/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/stm32l4xx_it.c 

OBJS += \
./Application/User/LIS2DH.o \
./Application/User/gpio.o \
./Application/User/i2c.o \
./Application/User/main.o \
./Application/User/stm32l4xx_hal_msp.o \
./Application/User/stm32l4xx_it.o 

C_DEPS += \
./Application/User/LIS2DH.d \
./Application/User/gpio.d \
./Application/User/i2c.d \
./Application/User/main.d \
./Application/User/stm32l4xx_hal_msp.d \
./Application/User/stm32l4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o: ../Application/User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/gpio.o: /Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/i2c.o: /Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: /Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32l4xx_hal_msp.o: /Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/stm32l4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32l4xx_it.o: /Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Src/stm32l4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/fabiomonteiro/dev/workspace/STM32L476RG/STM32-I2C/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


