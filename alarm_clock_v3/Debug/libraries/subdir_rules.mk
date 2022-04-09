################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
libraries/%.obj: ../libraries/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/Programs/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Programs/ti/ccs1040/ccs/ccs_base/arm/include" --include_path="D:/Programs/ti/ccs1040/ccs/ccs_base/arm/include/CMSIS" --include_path="D:/Programs/Code_Composer/workspace_v10/alarm_clock_v3" --include_path="D:/Programs/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="libraries/$(basename $(<F)).d_raw" --obj_directory="libraries" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


