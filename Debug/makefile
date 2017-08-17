################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS

GEN_OPTS += /Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/compiler.opt
GEN_OPTS__FLAG := --cmd_file="/Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/compiler.opt"
GEN_CMDS += /Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/linker.cmd
GEN_CMDS__FLAG := -l"/Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/configPkg/linker.cmd"

ORDERED_OBJS += \
"./MSP_EXP432P401R.obj" \
"./adc_dive.obj" \
"./alarm.obj" \
"./alarmtask.obj" \
"./blinkingledtask.obj" \
"./bsp.obj" \
"./bsp_led.obj" \
"./buttons_dive.obj" \
"./display_task.obj" \
"./dive_controller.obj" \
"./main.obj" \
"./protectedlcd.obj" \
"./scuba.obj" \
"./timertask.obj" \
"./LcdDriver/Crystalfontz128x128_ST7735.obj" \
"./LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" \
"./fonts/fontfixed6x8.obj" \
"../dive_computer.cmd" \
$(GEN_CMDS__FLAG) \
-l"/Users/munanxu/ti/simplelink_msp432_sdk_1_30_00_40/source/ti/display/lib/display.aem4f" \
-l"/Users/munanxu/ti/simplelink_msp432_sdk_1_30_00_40/source/ti/drivers/lib/drivers_msp432p4xx.aem4f" \
-l"/Users/munanxu/ti/simplelink_msp432_sdk_1_30_00_40/source/ti/grlib/ccs/grlib.lib" \
-l"/Users/munanxu/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/dpl/lib/dpl_msp432p4xx.aem4f" \
-l"/Users/munanxu/ti/simplelink_msp432_sdk_1_30_00_40/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include LcdDriver/subdir_vars.mk
-include fonts/subdir_vars.mk
-include subdir_rules.mk
-include LcdDriver/subdir_rules.mk
-include fonts/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
dive_computer.out \

EXE_OUTPUTS__QUOTED += \
"dive_computer.out" \

BIN_OUTPUTS += \
dive_computer.hex \

BIN_OUTPUTS__QUOTED += \
"dive_computer.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "dive_computer.out"

dependents:
	-cd /Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug && $(MAKE) all

# Tool invocations
dive_computer.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) /Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/tirtos_builds_MSP_EXP432P401R_release_ccs.lib
	@echo 'Building target: $@'
	@echo 'Invoking: MSP432 Linker'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power="all" --advice:power_severity=suppress --define=__MSP432P401R__ -g --c99 --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"dive_computer.map" -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/lib" -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="dive_computer_linkInfo.xml" --rom_model -o "dive_computer.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

dive_computer.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP432 Hex Utility'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armhex"  -o "dive_computer.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "MSP_EXP432P401R.obj" "adc_dive.obj" "alarm.obj" "alarmtask.obj" "blinkingledtask.obj" "bsp.obj" "bsp_led.obj" "buttons_dive.obj" "display_task.obj" "dive_controller.obj" "main.obj" "protectedlcd.obj" "scuba.obj" "timertask.obj" "LcdDriver/Crystalfontz128x128_ST7735.obj" "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" "fonts/fontfixed6x8.obj" 
	-$(RM) "MSP_EXP432P401R.d" "adc_dive.d" "alarm.d" "alarmtask.d" "blinkingledtask.d" "bsp.d" "bsp_led.d" "buttons_dive.d" "display_task.d" "dive_controller.d" "main.d" "protectedlcd.d" "scuba.d" "timertask.d" "LcdDriver/Crystalfontz128x128_ST7735.d" "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" "fonts/fontfixed6x8.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/munanxu/software_bootcamp/tirtos_builds_MSP_EXP432P401R_release_ccs/Debug/tirtos_builds_MSP_EXP432P401R_release_ccs.lib:

-include ../makefile.targets

