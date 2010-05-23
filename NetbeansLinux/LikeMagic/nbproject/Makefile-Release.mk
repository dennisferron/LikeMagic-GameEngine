#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractCppObjProxy.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractTypeSystem.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractExpression.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoBlock.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_from_script.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_to_script.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/TypeDescr.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractClass.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/RuntimeTypeSystem.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoVM.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=--std=c++0x -Wall -Werror=return-type -fdiagnostics-show-option -Wno-unused-variable
CXXFLAGS=--std=c++0x -Wall -Werror=return-type -fdiagnostics-show-option -Wno-unused-variable

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/liblikemagic.a

dist/Release/GNU-Linux-x86/liblikemagic.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${RM} dist/Release/GNU-Linux-x86/liblikemagic.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblikemagic.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/GNU-Linux-x86/liblikemagic.a

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractCppObjProxy.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/AbstractCppObjProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractCppObjProxy.o ../../Source/AbstractCppObjProxy.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractTypeSystem.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/AbstractTypeSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractTypeSystem.o ../../Source/AbstractTypeSystem.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractExpression.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/AbstractExpression.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractExpression.o ../../Source/AbstractExpression.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoBlock.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/IoBlock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoBlock.o ../../Source/IoBlock.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/API_Io.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io.o ../../Source/API_Io.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_from_script.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/API_Io_from_script.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_from_script.o ../../Source/API_Io_from_script.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_to_script.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/API_Io_to_script.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/API_Io_to_script.o ../../Source/API_Io_to_script.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/TypeDescr.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/TypeDescr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/TypeDescr.o ../../Source/TypeDescr.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractClass.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/AbstractClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/AbstractClass.o ../../Source/AbstractClass.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/RuntimeTypeSystem.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/RuntimeTypeSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/RuntimeTypeSystem.o ../../Source/RuntimeTypeSystem.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoVM.o: nbproject/Makefile-${CND_CONF}.mk ../../Source/IoVM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/local/../../Include/io -I../../Include -I/usr/local/include/boost-1_39 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/Source/IoVM.o ../../Source/IoVM.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/liblikemagic.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
