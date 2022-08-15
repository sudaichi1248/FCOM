#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-atsamd21g18a_default.mk)" "nbproject/Makefile-local-atsamd21g18a_default.mk"
include nbproject/Makefile-local-atsamd21g18a_default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=atsamd21g18a_default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c ../src/config/atsamd21g18a_default/system/int/src/sys_int.c ../src/config/atsamd21g18a_default/usb/src/usb_device.c ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c ../src/config/atsamd21g18a_default/initialization.c ../src/config/atsamd21g18a_default/interrupts.c ../src/config/atsamd21g18a_default/exceptions.c ../src/config/atsamd21g18a_default/startup_xc32.c ../src/config/atsamd21g18a_default/libc_syscalls.c ../src/config/atsamd21g18a_default/usb_device_init_data.c ../src/config/atsamd21g18a_default/tasks.c ../src/w25q128jv.c ../src/util.c ../src/s5851a.c ../src/lcd.c ../src/gpioexp.c ../src/rtc.c ../src/mlog.c ../src/sensor.c ../src/uart_debug.c ../src/uart_comm.c ../src/wpfm.c ../src/main.c ../src/app.c ../src/MATcore.c ../src/moni.c ../src/FOTAcmd.c ../src/version.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o ${OBJECTDIR}/_ext/1885044035/plib_adc.o ${OBJECTDIR}/_ext/950981355/plib_clock.o ${OBJECTDIR}/_ext/1885040036/plib_eic.o ${OBJECTDIR}/_ext/953130841/plib_evsys.o ${OBJECTDIR}/_ext/1693581925/plib_nvic.o ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o ${OBJECTDIR}/_ext/1324665920/plib_pm.o ${OBJECTDIR}/_ext/1693635076/plib_port.o ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o ${OBJECTDIR}/_ext/1324666034/plib_tc3.o ${OBJECTDIR}/_ext/1324666034/plib_tc4.o ${OBJECTDIR}/_ext/1324666034/plib_tc5.o ${OBJECTDIR}/_ext/9958233/xc32_monitor.o ${OBJECTDIR}/_ext/63538924/sys_int.o ${OBJECTDIR}/_ext/1572229207/usb_device.o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1640317663/initialization.o ${OBJECTDIR}/_ext/1640317663/interrupts.o ${OBJECTDIR}/_ext/1640317663/exceptions.o ${OBJECTDIR}/_ext/1640317663/startup_xc32.o ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o ${OBJECTDIR}/_ext/1640317663/tasks.o ${OBJECTDIR}/_ext/1360937237/w25q128jv.o ${OBJECTDIR}/_ext/1360937237/util.o ${OBJECTDIR}/_ext/1360937237/s5851a.o ${OBJECTDIR}/_ext/1360937237/lcd.o ${OBJECTDIR}/_ext/1360937237/gpioexp.o ${OBJECTDIR}/_ext/1360937237/rtc.o ${OBJECTDIR}/_ext/1360937237/mlog.o ${OBJECTDIR}/_ext/1360937237/sensor.o ${OBJECTDIR}/_ext/1360937237/uart_debug.o ${OBJECTDIR}/_ext/1360937237/uart_comm.o ${OBJECTDIR}/_ext/1360937237/wpfm.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/MATcore.o ${OBJECTDIR}/_ext/1360937237/moni.o ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o ${OBJECTDIR}/_ext/1360937237/version.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o.d ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o.d ${OBJECTDIR}/_ext/1885044035/plib_adc.o.d ${OBJECTDIR}/_ext/950981355/plib_clock.o.d ${OBJECTDIR}/_ext/1885040036/plib_eic.o.d ${OBJECTDIR}/_ext/953130841/plib_evsys.o.d ${OBJECTDIR}/_ext/1693581925/plib_nvic.o.d ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1324665920/plib_pm.o.d ${OBJECTDIR}/_ext/1693635076/plib_port.o.d ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o.d ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o.d ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o.d ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o.d ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o.d ${OBJECTDIR}/_ext/1324666034/plib_tc3.o.d ${OBJECTDIR}/_ext/1324666034/plib_tc4.o.d ${OBJECTDIR}/_ext/1324666034/plib_tc5.o.d ${OBJECTDIR}/_ext/9958233/xc32_monitor.o.d ${OBJECTDIR}/_ext/63538924/sys_int.o.d ${OBJECTDIR}/_ext/1572229207/usb_device.o.d ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o.d ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o.d ${OBJECTDIR}/_ext/1640317663/initialization.o.d ${OBJECTDIR}/_ext/1640317663/interrupts.o.d ${OBJECTDIR}/_ext/1640317663/exceptions.o.d ${OBJECTDIR}/_ext/1640317663/startup_xc32.o.d ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o.d ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o.d ${OBJECTDIR}/_ext/1640317663/tasks.o.d ${OBJECTDIR}/_ext/1360937237/w25q128jv.o.d ${OBJECTDIR}/_ext/1360937237/util.o.d ${OBJECTDIR}/_ext/1360937237/s5851a.o.d ${OBJECTDIR}/_ext/1360937237/lcd.o.d ${OBJECTDIR}/_ext/1360937237/gpioexp.o.d ${OBJECTDIR}/_ext/1360937237/rtc.o.d ${OBJECTDIR}/_ext/1360937237/mlog.o.d ${OBJECTDIR}/_ext/1360937237/sensor.o.d ${OBJECTDIR}/_ext/1360937237/uart_debug.o.d ${OBJECTDIR}/_ext/1360937237/uart_comm.o.d ${OBJECTDIR}/_ext/1360937237/wpfm.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/MATcore.o.d ${OBJECTDIR}/_ext/1360937237/moni.o.d ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o.d ${OBJECTDIR}/_ext/1360937237/version.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o ${OBJECTDIR}/_ext/1885044035/plib_adc.o ${OBJECTDIR}/_ext/950981355/plib_clock.o ${OBJECTDIR}/_ext/1885040036/plib_eic.o ${OBJECTDIR}/_ext/953130841/plib_evsys.o ${OBJECTDIR}/_ext/1693581925/plib_nvic.o ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o ${OBJECTDIR}/_ext/1324665920/plib_pm.o ${OBJECTDIR}/_ext/1693635076/plib_port.o ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o ${OBJECTDIR}/_ext/1324666034/plib_tc3.o ${OBJECTDIR}/_ext/1324666034/plib_tc4.o ${OBJECTDIR}/_ext/1324666034/plib_tc5.o ${OBJECTDIR}/_ext/9958233/xc32_monitor.o ${OBJECTDIR}/_ext/63538924/sys_int.o ${OBJECTDIR}/_ext/1572229207/usb_device.o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1640317663/initialization.o ${OBJECTDIR}/_ext/1640317663/interrupts.o ${OBJECTDIR}/_ext/1640317663/exceptions.o ${OBJECTDIR}/_ext/1640317663/startup_xc32.o ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o ${OBJECTDIR}/_ext/1640317663/tasks.o ${OBJECTDIR}/_ext/1360937237/w25q128jv.o ${OBJECTDIR}/_ext/1360937237/util.o ${OBJECTDIR}/_ext/1360937237/s5851a.o ${OBJECTDIR}/_ext/1360937237/lcd.o ${OBJECTDIR}/_ext/1360937237/gpioexp.o ${OBJECTDIR}/_ext/1360937237/rtc.o ${OBJECTDIR}/_ext/1360937237/mlog.o ${OBJECTDIR}/_ext/1360937237/sensor.o ${OBJECTDIR}/_ext/1360937237/uart_debug.o ${OBJECTDIR}/_ext/1360937237/uart_comm.o ${OBJECTDIR}/_ext/1360937237/wpfm.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/MATcore.o ${OBJECTDIR}/_ext/1360937237/moni.o ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o ${OBJECTDIR}/_ext/1360937237/version.o

# Source Files
SOURCEFILES=../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c ../src/config/atsamd21g18a_default/system/int/src/sys_int.c ../src/config/atsamd21g18a_default/usb/src/usb_device.c ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c ../src/config/atsamd21g18a_default/initialization.c ../src/config/atsamd21g18a_default/interrupts.c ../src/config/atsamd21g18a_default/exceptions.c ../src/config/atsamd21g18a_default/startup_xc32.c ../src/config/atsamd21g18a_default/libc_syscalls.c ../src/config/atsamd21g18a_default/usb_device_init_data.c ../src/config/atsamd21g18a_default/tasks.c ../src/w25q128jv.c ../src/util.c ../src/s5851a.c ../src/lcd.c ../src/gpioexp.c ../src/rtc.c ../src/mlog.c ../src/sensor.c ../src/uart_debug.c ../src/uart_comm.c ../src/wpfm.c ../src/main.c ../src/app.c ../src/MATcore.c ../src/moni.c ../src/FOTAcmd.c ../src/version.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=ATSAMD21G18A
ProjectDir="D:\FCOM\DLC\firmware\wpfm5.X"
ProjectName=wpfm5
ConfName=atsamd21g18a_default
ImagePath="${DISTDIR}\wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
ImageName="wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-atsamd21g18a_default.mk ${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [..\..\HEX2MOT ${ImagePath} ]"
	@..\..\HEX2MOT ${ImagePath} 
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATSAMD21G18A
MP_LINKER_FILE_OPTION=,--script="..\src\config\atsamd21g18a_default\ATSAMD21G18A.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o: ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c  .generated_files/flags/atsamd21g18a_default/74d9f960123743cc105290a3c49342ad6ba7c65f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1814754785" 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o.d" -o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o: ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c  .generated_files/flags/atsamd21g18a_default/2d74ffe95e21108fc18bd36c48be80bff9c5d83f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1814754785" 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o.d" -o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885044035/plib_adc.o: ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c  .generated_files/flags/atsamd21g18a_default/a9589416b4a6b2f1591b6a9eab0d34ff63ff8d1f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1885044035" 
	@${RM} ${OBJECTDIR}/_ext/1885044035/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885044035/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885044035/plib_adc.o.d" -o ${OBJECTDIR}/_ext/1885044035/plib_adc.o ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/950981355/plib_clock.o: ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c  .generated_files/flags/atsamd21g18a_default/eaf6498d6457a786921bef7310ba0de77bbb3fc2 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/950981355" 
	@${RM} ${OBJECTDIR}/_ext/950981355/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/950981355/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/950981355/plib_clock.o.d" -o ${OBJECTDIR}/_ext/950981355/plib_clock.o ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885040036/plib_eic.o: ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c  .generated_files/flags/atsamd21g18a_default/931c2b65798c4c99a1c652566bfa56ab64c3239a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1885040036" 
	@${RM} ${OBJECTDIR}/_ext/1885040036/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885040036/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885040036/plib_eic.o.d" -o ${OBJECTDIR}/_ext/1885040036/plib_eic.o ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/953130841/plib_evsys.o: ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c  .generated_files/flags/atsamd21g18a_default/e77b1204e2e8b09275c222bb0ccb6d60d6fc5d67 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/953130841" 
	@${RM} ${OBJECTDIR}/_ext/953130841/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/953130841/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/953130841/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/953130841/plib_evsys.o ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1693581925/plib_nvic.o: ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c  .generated_files/flags/atsamd21g18a_default/c0fa89a5a5a7d0d93fe2b8e911323223fe2b88b9 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1693581925" 
	@${RM} ${OBJECTDIR}/_ext/1693581925/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693581925/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1693581925/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1693581925/plib_nvic.o ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o: ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/atsamd21g18a_default/bd5fd0f63728cbbf6e82c8c17ef6d9c4c8b8070b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/522110765" 
	@${RM} ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324665920/plib_pm.o: ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c  .generated_files/flags/atsamd21g18a_default/4a3b010ef5288f01fd1ef38c5eb4a1e3b07206cb .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324665920" 
	@${RM} ${OBJECTDIR}/_ext/1324665920/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324665920/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324665920/plib_pm.o.d" -o ${OBJECTDIR}/_ext/1324665920/plib_pm.o ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1693635076/plib_port.o: ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c  .generated_files/flags/atsamd21g18a_default/badf98fa61876817c173ee5f2782c4e60324554b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1693635076" 
	@${RM} ${OBJECTDIR}/_ext/1693635076/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693635076/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1693635076/plib_port.o.d" -o ${OBJECTDIR}/_ext/1693635076/plib_port.o ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o: ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c  .generated_files/flags/atsamd21g18a_default/496f2c4fe22f0c775a26a3a86ab50dcce48d6808 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/163103410" 
	@${RM} ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o.d" -o ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o: ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c  .generated_files/flags/atsamd21g18a_default/b9a5c4260f7abccb799cc9e236ee42161fa0d646 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/328131232" 
	@${RM} ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o.d" -o ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c  .generated_files/flags/atsamd21g18a_default/dceeee1ad99312524031c3b7e9ce25b0377c6c56 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/atsamd21g18a_default/ede3e8c5ebd8f99dee0953b0c816f3b1865d180b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c  .generated_files/flags/atsamd21g18a_default/47d0f627ad913c995e76b7f6f5247cad926e83b5 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc3.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c  .generated_files/flags/atsamd21g18a_default/3e3546a4519318895903a69461c5d2794d57cb0a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc3.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc3.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc4.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c  .generated_files/flags/atsamd21g18a_default/bb40ed13e02beb2d19fdad61fb7012e6fe281194 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc4.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc5.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c  .generated_files/flags/atsamd21g18a_default/dacd650b10e8de2396f25209ca558dca6dd020f9 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc5.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc5.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/9958233/xc32_monitor.o: ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c  .generated_files/flags/atsamd21g18a_default/62509924069223583a04c203ae2b4c414454bf6a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/9958233" 
	@${RM} ${OBJECTDIR}/_ext/9958233/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/9958233/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/9958233/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/9958233/xc32_monitor.o ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/63538924/sys_int.o: ../src/config/atsamd21g18a_default/system/int/src/sys_int.c  .generated_files/flags/atsamd21g18a_default/8bbbce6848db7118d95a8183cd4ba266c5e0b023 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/63538924" 
	@${RM} ${OBJECTDIR}/_ext/63538924/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/63538924/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/63538924/sys_int.o.d" -o ${OBJECTDIR}/_ext/63538924/sys_int.o ../src/config/atsamd21g18a_default/system/int/src/sys_int.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device.o: ../src/config/atsamd21g18a_default/usb/src/usb_device.c  .generated_files/flags/atsamd21g18a_default/cb3d46361694c25843afa7087b5ace01e41431cd .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device.o ../src/config/atsamd21g18a_default/usb/src/usb_device.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o: ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c  .generated_files/flags/atsamd21g18a_default/c9ff29593088930d0c26263fad01272fa2b40ea1 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o: ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c  .generated_files/flags/atsamd21g18a_default/b361d25a0aea25ba1259facfcb2e92c7a2bb6ae1 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/initialization.o: ../src/config/atsamd21g18a_default/initialization.c  .generated_files/flags/atsamd21g18a_default/96d422d604178c507ad68fd574be8f37612be0b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/initialization.o.d" -o ${OBJECTDIR}/_ext/1640317663/initialization.o ../src/config/atsamd21g18a_default/initialization.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/interrupts.o: ../src/config/atsamd21g18a_default/interrupts.c  .generated_files/flags/atsamd21g18a_default/ed6116cd07186301bb6bfe9370c49896d159b692 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/interrupts.o.d" -o ${OBJECTDIR}/_ext/1640317663/interrupts.o ../src/config/atsamd21g18a_default/interrupts.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/exceptions.o: ../src/config/atsamd21g18a_default/exceptions.c  .generated_files/flags/atsamd21g18a_default/f1ea110183684aa6e36ba23e76c263d2f6d368ad .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/exceptions.o.d" -o ${OBJECTDIR}/_ext/1640317663/exceptions.o ../src/config/atsamd21g18a_default/exceptions.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/startup_xc32.o: ../src/config/atsamd21g18a_default/startup_xc32.c  .generated_files/flags/atsamd21g18a_default/f9293bf8e33694387eea9c1f844492bb6bbf7051 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1640317663/startup_xc32.o ../src/config/atsamd21g18a_default/startup_xc32.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/libc_syscalls.o: ../src/config/atsamd21g18a_default/libc_syscalls.c  .generated_files/flags/atsamd21g18a_default/9eb7b162f5951adf1e5115f3270486306c52442e .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o ../src/config/atsamd21g18a_default/libc_syscalls.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o: ../src/config/atsamd21g18a_default/usb_device_init_data.c  .generated_files/flags/atsamd21g18a_default/91d6829c5bc3d76b775b846814fcdb9c8c4a1e4c .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o ../src/config/atsamd21g18a_default/usb_device_init_data.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/tasks.o: ../src/config/atsamd21g18a_default/tasks.c  .generated_files/flags/atsamd21g18a_default/387d70171990a18ac8f22676d655a83b81d75dab .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/tasks.o.d" -o ${OBJECTDIR}/_ext/1640317663/tasks.o ../src/config/atsamd21g18a_default/tasks.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/w25q128jv.o: ../src/w25q128jv.c  .generated_files/flags/atsamd21g18a_default/ce3310ac145e7a55acbf55d516ed2cf71e0c3e26 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/w25q128jv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/w25q128jv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/w25q128jv.o.d" -o ${OBJECTDIR}/_ext/1360937237/w25q128jv.o ../src/w25q128jv.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/util.o: ../src/util.c  .generated_files/flags/atsamd21g18a_default/d5ebf6a61d1c469f6d31e0ce107080ae80be30ff .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/util.o.d" -o ${OBJECTDIR}/_ext/1360937237/util.o ../src/util.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/s5851a.o: ../src/s5851a.c  .generated_files/flags/atsamd21g18a_default/f9c53a143f701638e1753b9386f52235eda11469 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/s5851a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/s5851a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/s5851a.o.d" -o ${OBJECTDIR}/_ext/1360937237/s5851a.o ../src/s5851a.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/lcd.o: ../src/lcd.c  .generated_files/flags/atsamd21g18a_default/d3c86fa14b586c0180efc671f438f749ad140e8d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/lcd.o.d" -o ${OBJECTDIR}/_ext/1360937237/lcd.o ../src/lcd.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/gpioexp.o: ../src/gpioexp.c  .generated_files/flags/atsamd21g18a_default/63e6b064180ee816f9926d9fba783a437a2d879d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpioexp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpioexp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gpioexp.o.d" -o ${OBJECTDIR}/_ext/1360937237/gpioexp.o ../src/gpioexp.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/rtc.o: ../src/rtc.c  .generated_files/flags/atsamd21g18a_default/3843cd82148c367128b968f51738aaf3b283e6c0 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/rtc.o.d" -o ${OBJECTDIR}/_ext/1360937237/rtc.o ../src/rtc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/mlog.o: ../src/mlog.c  .generated_files/flags/atsamd21g18a_default/fbe58f767d8140a61c76c55ae64b259cc499b419 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mlog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mlog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/mlog.o.d" -o ${OBJECTDIR}/_ext/1360937237/mlog.o ../src/mlog.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/sensor.o: ../src/sensor.c  .generated_files/flags/atsamd21g18a_default/82b2a39ce8d9d4616e8bcb6934ef6921e93bda8a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor.o ../src/sensor.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/uart_debug.o: ../src/uart_debug.c  .generated_files/flags/atsamd21g18a_default/d222e940570ac0996d888fd360beb384b44d87b7 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_debug.o ../src/uart_debug.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/uart_comm.o: ../src/uart_comm.c  .generated_files/flags/atsamd21g18a_default/64abb1a52bce38961a5804d84c94ff6bdd63f330 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_comm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_comm.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_comm.o ../src/uart_comm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/wpfm.o: ../src/wpfm.c  .generated_files/flags/atsamd21g18a_default/2bd17a3458d2959724d701d13d83225a3f6130 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wpfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wpfm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/wpfm.o.d" -o ${OBJECTDIR}/_ext/1360937237/wpfm.o ../src/wpfm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/atsamd21g18a_default/e10055ab358bd7cae15c18f44ad7d62e8b99faaf .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/atsamd21g18a_default/455b8654e9f32558cc833f909cf9b11a4d6d8878 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/MATcore.o: ../src/MATcore.c  .generated_files/flags/atsamd21g18a_default/a8d174bda3b0950f2e6fd45c6bbf55ad3836be0d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MATcore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MATcore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/MATcore.o.d" -o ${OBJECTDIR}/_ext/1360937237/MATcore.o ../src/MATcore.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/moni.o: ../src/moni.c  .generated_files/flags/atsamd21g18a_default/3ccfe46cb551117c3d9ed8b6227a173d264d6bce .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moni.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moni.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/moni.o.d" -o ${OBJECTDIR}/_ext/1360937237/moni.o ../src/moni.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/FOTAcmd.o: ../src/FOTAcmd.c  .generated_files/flags/atsamd21g18a_default/acbf10f8bf175a4af3c32951511fd232c0716412 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/FOTAcmd.o.d" -o ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o ../src/FOTAcmd.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/version.o: ../src/version.c  .generated_files/flags/atsamd21g18a_default/9ab34229be2eb3bacbbbceeac01e8cf9688ab43f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/version.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/version.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/version.o.d" -o ${OBJECTDIR}/_ext/1360937237/version.o ../src/version.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o: ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c  .generated_files/flags/atsamd21g18a_default/73ba43e85ee5e8d74b5b504328443848876ffa2a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1814754785" 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o.d" -o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1.o ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o: ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c  .generated_files/flags/atsamd21g18a_default/b6964cb6cf73d52a312ceb8b803a375f3bdcab3d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1814754785" 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o.d" -o ${OBJECTDIR}/_ext/1814754785/drv_usbfsv1_device.o ../src/config/atsamd21g18a_default/driver/usb/usbfsv1/src/drv_usbfsv1_device.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885044035/plib_adc.o: ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c  .generated_files/flags/atsamd21g18a_default/2974a4dc10999c0eb7fd8c9dffc22a050d64e493 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1885044035" 
	@${RM} ${OBJECTDIR}/_ext/1885044035/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885044035/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885044035/plib_adc.o.d" -o ${OBJECTDIR}/_ext/1885044035/plib_adc.o ../src/config/atsamd21g18a_default/peripheral/adc/plib_adc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/950981355/plib_clock.o: ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c  .generated_files/flags/atsamd21g18a_default/7336d626ae0a33de30859be045ae45b98f904dbd .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/950981355" 
	@${RM} ${OBJECTDIR}/_ext/950981355/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/950981355/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/950981355/plib_clock.o.d" -o ${OBJECTDIR}/_ext/950981355/plib_clock.o ../src/config/atsamd21g18a_default/peripheral/clock/plib_clock.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1885040036/plib_eic.o: ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c  .generated_files/flags/atsamd21g18a_default/207ed9a44701b4b0fea18dad2baef4e4e492acc4 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1885040036" 
	@${RM} ${OBJECTDIR}/_ext/1885040036/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1885040036/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1885040036/plib_eic.o.d" -o ${OBJECTDIR}/_ext/1885040036/plib_eic.o ../src/config/atsamd21g18a_default/peripheral/eic/plib_eic.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/953130841/plib_evsys.o: ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c  .generated_files/flags/atsamd21g18a_default/2fc299a7acbd7697647d07ae1ffe254ee2b599b1 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/953130841" 
	@${RM} ${OBJECTDIR}/_ext/953130841/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/953130841/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/953130841/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/953130841/plib_evsys.o ../src/config/atsamd21g18a_default/peripheral/evsys/plib_evsys.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1693581925/plib_nvic.o: ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c  .generated_files/flags/atsamd21g18a_default/9011451420378a95f75a7984a38eb6f7d684592e .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1693581925" 
	@${RM} ${OBJECTDIR}/_ext/1693581925/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693581925/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1693581925/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1693581925/plib_nvic.o ../src/config/atsamd21g18a_default/peripheral/nvic/plib_nvic.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o: ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/atsamd21g18a_default/414d02a637852b1d6408bbae5c96cdaf15aeff5d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/522110765" 
	@${RM} ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/522110765/plib_nvmctrl.o ../src/config/atsamd21g18a_default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324665920/plib_pm.o: ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c  .generated_files/flags/atsamd21g18a_default/8d410c0f6c58578f648e3562caf0d6453e00bd51 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324665920" 
	@${RM} ${OBJECTDIR}/_ext/1324665920/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324665920/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324665920/plib_pm.o.d" -o ${OBJECTDIR}/_ext/1324665920/plib_pm.o ../src/config/atsamd21g18a_default/peripheral/pm/plib_pm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1693635076/plib_port.o: ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c  .generated_files/flags/atsamd21g18a_default/44182c3aab46c85174cc878739f19231102c778a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1693635076" 
	@${RM} ${OBJECTDIR}/_ext/1693635076/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693635076/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1693635076/plib_port.o.d" -o ${OBJECTDIR}/_ext/1693635076/plib_port.o ../src/config/atsamd21g18a_default/peripheral/port/plib_port.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o: ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c  .generated_files/flags/atsamd21g18a_default/ac4ffbcedc6a9b4052908d62f75f37ac371ac62a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/163103410" 
	@${RM} ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o.d" -o ${OBJECTDIR}/_ext/163103410/plib_sercom3_i2c_master.o ../src/config/atsamd21g18a_default/peripheral/sercom/i2c_master/plib_sercom3_i2c_master.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o: ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c  .generated_files/flags/atsamd21g18a_default/bfbef279ebb33dd2bd5bcf0c240811dafbb1026f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/328131232" 
	@${RM} ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o.d" -o ${OBJECTDIR}/_ext/328131232/plib_sercom1_spi_master.o ../src/config/atsamd21g18a_default/peripheral/sercom/spi_master/plib_sercom1_spi_master.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c  .generated_files/flags/atsamd21g18a_default/63dc7889f21e04993b25686b72a5afb07731ac2 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom0_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom0_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c  .generated_files/flags/atsamd21g18a_default/d651c0cb008d309b8d6e4cea0936c3d3b34b05b4 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom5_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom5_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o: ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c  .generated_files/flags/atsamd21g18a_default/397933eeaf71318976c3d5c9dcbdf0a659ade7e4 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/472979226" 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o.d" -o ${OBJECTDIR}/_ext/472979226/plib_sercom2_usart.o ../src/config/atsamd21g18a_default/peripheral/sercom/usart/plib_sercom2_usart.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc3.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c  .generated_files/flags/atsamd21g18a_default/da19fd6b5a25910166f08ef69f1e380f200ad235 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc3.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc3.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc3.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc4.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c  .generated_files/flags/atsamd21g18a_default/80f0a9a55687cbd0e282b643caec975c303ce43a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc4.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc4.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1324666034/plib_tc5.o: ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c  .generated_files/flags/atsamd21g18a_default/3d06f25bba031973eb88fe819969d44680f93b93 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1324666034" 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324666034/plib_tc5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1324666034/plib_tc5.o.d" -o ${OBJECTDIR}/_ext/1324666034/plib_tc5.o ../src/config/atsamd21g18a_default/peripheral/tc/plib_tc5.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/9958233/xc32_monitor.o: ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c  .generated_files/flags/atsamd21g18a_default/a3163b22f698064b7dcf682e4fdec371f9b8d4a4 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/9958233" 
	@${RM} ${OBJECTDIR}/_ext/9958233/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/9958233/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/9958233/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/9958233/xc32_monitor.o ../src/config/atsamd21g18a_default/stdio/xc32_monitor.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/63538924/sys_int.o: ../src/config/atsamd21g18a_default/system/int/src/sys_int.c  .generated_files/flags/atsamd21g18a_default/b90c4651447cb50dba20406774e45ce1cd569973 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/63538924" 
	@${RM} ${OBJECTDIR}/_ext/63538924/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/63538924/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/63538924/sys_int.o.d" -o ${OBJECTDIR}/_ext/63538924/sys_int.o ../src/config/atsamd21g18a_default/system/int/src/sys_int.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device.o: ../src/config/atsamd21g18a_default/usb/src/usb_device.c  .generated_files/flags/atsamd21g18a_default/bc194e49735b252cd4160f064b1f0498c0e5b639 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device.o ../src/config/atsamd21g18a_default/usb/src/usb_device.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o: ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c  .generated_files/flags/atsamd21g18a_default/879e1e11da6e0f870c19bbf5d2f50269de0a6a3d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc.o ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o: ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c  .generated_files/flags/atsamd21g18a_default/39de57c08d1a34f246f1711930837044abd9ecf7 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1572229207" 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/1572229207/usb_device_cdc_acm.o ../src/config/atsamd21g18a_default/usb/src/usb_device_cdc_acm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/initialization.o: ../src/config/atsamd21g18a_default/initialization.c  .generated_files/flags/atsamd21g18a_default/295281f1b2879547bc6610671d8d31e918ba1384 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/initialization.o.d" -o ${OBJECTDIR}/_ext/1640317663/initialization.o ../src/config/atsamd21g18a_default/initialization.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/interrupts.o: ../src/config/atsamd21g18a_default/interrupts.c  .generated_files/flags/atsamd21g18a_default/4f1342ddc3582632d83a9f170d129af21b78a7d3 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/interrupts.o.d" -o ${OBJECTDIR}/_ext/1640317663/interrupts.o ../src/config/atsamd21g18a_default/interrupts.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/exceptions.o: ../src/config/atsamd21g18a_default/exceptions.c  .generated_files/flags/atsamd21g18a_default/7115e9b3e54fbd6d5b2392187e79b7fecac0153b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/exceptions.o.d" -o ${OBJECTDIR}/_ext/1640317663/exceptions.o ../src/config/atsamd21g18a_default/exceptions.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/startup_xc32.o: ../src/config/atsamd21g18a_default/startup_xc32.c  .generated_files/flags/atsamd21g18a_default/fd3c92b67af89144dc63266e51817fca3c3e4cf .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1640317663/startup_xc32.o ../src/config/atsamd21g18a_default/startup_xc32.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/libc_syscalls.o: ../src/config/atsamd21g18a_default/libc_syscalls.c  .generated_files/flags/atsamd21g18a_default/8d245a8ecca5ed206223a1035dfcaa13deee8f6c .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1640317663/libc_syscalls.o ../src/config/atsamd21g18a_default/libc_syscalls.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o: ../src/config/atsamd21g18a_default/usb_device_init_data.c  .generated_files/flags/atsamd21g18a_default/981e3915460f5f585e2cea8f89943639c33f6059 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1640317663/usb_device_init_data.o ../src/config/atsamd21g18a_default/usb_device_init_data.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1640317663/tasks.o: ../src/config/atsamd21g18a_default/tasks.c  .generated_files/flags/atsamd21g18a_default/48deb2332edb9d529173de874269ceca10e8fd2e .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1640317663" 
	@${RM} ${OBJECTDIR}/_ext/1640317663/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640317663/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1640317663/tasks.o.d" -o ${OBJECTDIR}/_ext/1640317663/tasks.o ../src/config/atsamd21g18a_default/tasks.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/w25q128jv.o: ../src/w25q128jv.c  .generated_files/flags/atsamd21g18a_default/a8ca0998b8abdddf451fc518fecb1fb161242778 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/w25q128jv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/w25q128jv.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/w25q128jv.o.d" -o ${OBJECTDIR}/_ext/1360937237/w25q128jv.o ../src/w25q128jv.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/util.o: ../src/util.c  .generated_files/flags/atsamd21g18a_default/d6d6a6cb9218e4dd41b41e1ead55b17bb2dc4c5a .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/util.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/util.o.d" -o ${OBJECTDIR}/_ext/1360937237/util.o ../src/util.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/s5851a.o: ../src/s5851a.c  .generated_files/flags/atsamd21g18a_default/de82f4ca5ada8b57343534ba2d132c093b4f817e .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/s5851a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/s5851a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/s5851a.o.d" -o ${OBJECTDIR}/_ext/1360937237/s5851a.o ../src/s5851a.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/lcd.o: ../src/lcd.c  .generated_files/flags/atsamd21g18a_default/6437b97bb853f611aad39c1268a1b23b384040f5 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/lcd.o.d" -o ${OBJECTDIR}/_ext/1360937237/lcd.o ../src/lcd.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/gpioexp.o: ../src/gpioexp.c  .generated_files/flags/atsamd21g18a_default/7a85887b45de66e3f76c6a3842c3ac0f1fa39ee6 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpioexp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpioexp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gpioexp.o.d" -o ${OBJECTDIR}/_ext/1360937237/gpioexp.o ../src/gpioexp.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/rtc.o: ../src/rtc.c  .generated_files/flags/atsamd21g18a_default/186f4d43ea4386e43f7221e87da98bffb3a52e68 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rtc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/rtc.o.d" -o ${OBJECTDIR}/_ext/1360937237/rtc.o ../src/rtc.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/mlog.o: ../src/mlog.c  .generated_files/flags/atsamd21g18a_default/81d72a853f0a74eecd2b7401537aa35d62dbb7b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mlog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mlog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/mlog.o.d" -o ${OBJECTDIR}/_ext/1360937237/mlog.o ../src/mlog.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/sensor.o: ../src/sensor.c  .generated_files/flags/atsamd21g18a_default/696763d326c7af2cc5cdeff29938331bfa880e7 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor.o ../src/sensor.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/uart_debug.o: ../src/uart_debug.c  .generated_files/flags/atsamd21g18a_default/53eaca6d70fd1b0270a0cfea09ecf5e1727bd196 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_debug.o ../src/uart_debug.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/uart_comm.o: ../src/uart_comm.c  .generated_files/flags/atsamd21g18a_default/8407fa88e18066a8c2b1145e6cd96a6680b4b81b .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_comm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_comm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_comm.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_comm.o ../src/uart_comm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/wpfm.o: ../src/wpfm.c  .generated_files/flags/atsamd21g18a_default/c8acaf3850852a9ba86141d581a81dfb24069dc3 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wpfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wpfm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/wpfm.o.d" -o ${OBJECTDIR}/_ext/1360937237/wpfm.o ../src/wpfm.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/atsamd21g18a_default/74e7c0e37a150bbb0178438a2980ca3b8511191f .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/atsamd21g18a_default/b2f62011b8fad699765a94fbd167f8f8e9173670 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/MATcore.o: ../src/MATcore.c  .generated_files/flags/atsamd21g18a_default/9e7716fba6c7f975a280379a7938751ac6e16804 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MATcore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/MATcore.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/MATcore.o.d" -o ${OBJECTDIR}/_ext/1360937237/MATcore.o ../src/MATcore.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/moni.o: ../src/moni.c  .generated_files/flags/atsamd21g18a_default/1d8670cc45725f2268168243efca8a4e3aaaf21d .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moni.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/moni.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/moni.o.d" -o ${OBJECTDIR}/_ext/1360937237/moni.o ../src/moni.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/FOTAcmd.o: ../src/FOTAcmd.c  .generated_files/flags/atsamd21g18a_default/e302d7c622284559d65bb8666fede4c974caa8f2 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/FOTAcmd.o.d" -o ${OBJECTDIR}/_ext/1360937237/FOTAcmd.o ../src/FOTAcmd.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/version.o: ../src/version.c  .generated_files/flags/atsamd21g18a_default/7e406dea497bf391b38e7a72c4724a2bb141b650 .generated_files/flags/atsamd21g18a_default/371f82de429950eaa99b35fa67f9d4c59ae13e52
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/version.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/version.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/atsamd21g18a_default" -I"../src/packs/ATSAMD21G18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/version.o.d" -o ${OBJECTDIR}/_ext/1360937237/version.o ../src/version.c    -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samd21a" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/atsamd21g18a_default/ATSAMD21G18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o ${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samd21a"
	
else
${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/atsamd21g18a_default/ATSAMD21G18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o ${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_atsamd21g18a_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/samd21a"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.hex -o${DISTDIR}/wpfm5.X.${IMAGE_TYPE}.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
