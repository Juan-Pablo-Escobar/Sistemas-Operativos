################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pSemCreate.c \
../src/pSemPost.c \
../src/pSemWait.c 

OBJS += \
./src/pSemCreate.o \
./src/pSemPost.o \
./src/pSemWait.o 

C_DEPS += \
./src/pSemCreate.d \
./src/pSemPost.d \
./src/pSemWait.d 


# Each subdirectory must supply rules for building sources it contributes
src/pSemCreate.o: ../src/pSemCreate.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/pSemCreate.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


