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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/characters/Bullet.o \
	${OBJECTDIR}/src/characters/Character.o \
	${OBJECTDIR}/src/characters/Ghost.o \
	${OBJECTDIR}/src/characters/Player.o \
	${OBJECTDIR}/src/engine/InputDriver.o \
	${OBJECTDIR}/src/engine/SignalManager.o \
	${OBJECTDIR}/src/engine/TextureManager.o \
	${OBJECTDIR}/src/engine/VideoDriver.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/ui/UIBox.o \
	${OBJECTDIR}/src/ui/UIElement.o \
	${OBJECTDIR}/src/ui/UIIcon.o \
	${OBJECTDIR}/src/ui/UILabel.o \
	${OBJECTDIR}/src/ui/UIManager.o \
	${OBJECTDIR}/src/world/Pickup.o \
	${OBJECTDIR}/src/world/WorldManager.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/homedefence

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/homedefence: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/homedefence ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Game.o: src/Game.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/characters/Bullet.o: src/characters/Bullet.cpp
	${MKDIR} -p ${OBJECTDIR}/src/characters
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/characters/Bullet.o src/characters/Bullet.cpp

${OBJECTDIR}/src/characters/Character.o: src/characters/Character.cpp
	${MKDIR} -p ${OBJECTDIR}/src/characters
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/characters/Character.o src/characters/Character.cpp

${OBJECTDIR}/src/characters/Ghost.o: src/characters/Ghost.cpp
	${MKDIR} -p ${OBJECTDIR}/src/characters
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/characters/Ghost.o src/characters/Ghost.cpp

${OBJECTDIR}/src/characters/Player.o: src/characters/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/src/characters
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/characters/Player.o src/characters/Player.cpp

${OBJECTDIR}/src/engine/InputDriver.o: src/engine/InputDriver.cpp
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/engine/InputDriver.o src/engine/InputDriver.cpp

${OBJECTDIR}/src/engine/SignalManager.o: src/engine/SignalManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/engine/SignalManager.o src/engine/SignalManager.cpp

${OBJECTDIR}/src/engine/TextureManager.o: src/engine/TextureManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/engine/TextureManager.o src/engine/TextureManager.cpp

${OBJECTDIR}/src/engine/VideoDriver.o: src/engine/VideoDriver.cpp
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/engine/VideoDriver.o src/engine/VideoDriver.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/ui/UIBox.o: src/ui/UIBox.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIBox.o src/ui/UIBox.cpp

${OBJECTDIR}/src/ui/UIElement.o: src/ui/UIElement.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIElement.o src/ui/UIElement.cpp

${OBJECTDIR}/src/ui/UIIcon.o: src/ui/UIIcon.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIIcon.o src/ui/UIIcon.cpp

${OBJECTDIR}/src/ui/UILabel.o: src/ui/UILabel.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UILabel.o src/ui/UILabel.cpp

${OBJECTDIR}/src/ui/UIManager.o: src/ui/UIManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIManager.o src/ui/UIManager.cpp

${OBJECTDIR}/src/world/Pickup.o: src/world/Pickup.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/Pickup.o src/world/Pickup.cpp

${OBJECTDIR}/src/world/WorldManager.o: src/world/WorldManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/WorldManager.o src/world/WorldManager.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
