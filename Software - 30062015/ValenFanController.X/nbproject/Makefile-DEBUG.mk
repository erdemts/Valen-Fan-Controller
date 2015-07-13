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
ifeq "$(wildcard nbproject/Makefile-local-DEBUG.mk)" "nbproject/Makefile-local-DEBUG.mk"
include nbproject/Makefile-local-DEBUG.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=DEBUG
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/adc.c ../src/main.c ../src/uart.c ../src/one_wire.c ../src/vhn5019.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/adc.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/uart.p1 ${OBJECTDIR}/_ext/1360937237/one_wire.p1 ${OBJECTDIR}/_ext/1360937237/vhn5019.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/adc.p1.d ${OBJECTDIR}/_ext/1360937237/main.p1.d ${OBJECTDIR}/_ext/1360937237/uart.p1.d ${OBJECTDIR}/_ext/1360937237/one_wire.p1.d ${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/adc.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/uart.p1 ${OBJECTDIR}/_ext/1360937237/one_wire.p1 ${OBJECTDIR}/_ext/1360937237/vhn5019.p1

# Source Files
SOURCEFILES=../src/adc.c ../src/main.c ../src/uart.c ../src/one_wire.c ../src/vhn5019.c


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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-DEBUG.mk dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F887
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/adc.p1: ../src/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/adc.p1: > ${OBJECTDIR}/_ext/1360937237/adc.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/adc.dep >> ${OBJECTDIR}/_ext/1360937237/adc.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/adc.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/main.p1: > ${OBJECTDIR}/_ext/1360937237/main.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/main.dep >> ${OBJECTDIR}/_ext/1360937237/main.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/uart.p1: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/uart.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/uart.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/uart.p1: > ${OBJECTDIR}/_ext/1360937237/uart.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/uart.dep >> ${OBJECTDIR}/_ext/1360937237/uart.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/one_wire.p1: ../src/one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/one_wire.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/one_wire.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/one_wire.p1: > ${OBJECTDIR}/_ext/1360937237/one_wire.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/one_wire.dep >> ${OBJECTDIR}/_ext/1360937237/one_wire.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/one_wire.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/vhn5019.p1: ../src/vhn5019.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/vhn5019.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/vhn5019.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/vhn5019.p1: > ${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/vhn5019.dep >> ${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360937237/adc.p1: ../src/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/adc.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/adc.p1: > ${OBJECTDIR}/_ext/1360937237/adc.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/adc.dep >> ${OBJECTDIR}/_ext/1360937237/adc.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/adc.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/main.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/main.p1: > ${OBJECTDIR}/_ext/1360937237/main.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/main.dep >> ${OBJECTDIR}/_ext/1360937237/main.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/uart.p1: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/uart.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/uart.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/uart.p1: > ${OBJECTDIR}/_ext/1360937237/uart.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/uart.dep >> ${OBJECTDIR}/_ext/1360937237/uart.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/one_wire.p1: ../src/one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/one_wire.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/one_wire.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/one_wire.p1: > ${OBJECTDIR}/_ext/1360937237/one_wire.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/one_wire.dep >> ${OBJECTDIR}/_ext/1360937237/one_wire.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/one_wire.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/vhn5019.p1: ../src/vhn5019.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	${MP_CC} --pass1 ../src/vhn5019.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@${MP_CC} --scandep  ../src/vhn5019.c $(MP_EXTRA_CC_PRE) -q --chip=$(MP_PROCESSOR_OPTION) -P  --outdir="${OBJECTDIR}\_ext\1360937237" -N31 -I"../src" -I"../include" --warn=0 --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --opt=default,+asm,-asmfile,-speed,+space,-debug,9  --double=24 --float=24 --addrqual=ignore --mode=pro -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s"
	@echo ${OBJECTDIR}/_ext/1360937237/vhn5019.p1: > ${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d
	@cat ${OBJECTDIR}/_ext/1360937237/vhn5019.dep >> ${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/vhn5019.p1.d" $(SILENT) -ht  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -D__DEBUG --debugger=realice -N31 -I"../src" -I"../include" --warn=0  --double=24 --float=24 --addrqual=ignore --mode=pro --output=default,-inhx032 -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s" ${OBJECTFILES_QUOTED_IF_SPACED}  
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.hex
else
dist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) -odist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -mdist/${CND_CONF}/${IMAGE_TYPE}/ValenFanController.X.${IMAGE_TYPE}.map --summary=default,-psect,-class,+mem,-hex --chip=$(MP_PROCESSOR_OPTION) -P --runtime=default,+clear,+init,-keep,+osccal,-resetbits,-download,-stackcall,+clib --summary=default,-psect,-class,+mem,-hex --opt=default,+asm,-asmfile,-speed,+space,-debug,9 -N31 -I"../src" -I"../include" --warn=0  --double=24 --float=24 --addrqual=ignore --mode=pro --output=default,-inhx032 -g --asmlist "--errformat=%f:%l: error: %s" "--msgformat=%f:%l: advisory: %s" "--warnformat=%f:%l warning: %s" ${OBJECTFILES_QUOTED_IF_SPACED}  
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/DEBUG
	${RM} -r dist/DEBUG

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
