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
include HomeDefence-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/characters/Bullet.o \
	${OBJECTDIR}/src/characters/Character.o \
	${OBJECTDIR}/src/characters/Gem.o \
	${OBJECTDIR}/src/characters/Ghost.o \
	${OBJECTDIR}/src/characters/Player.o \
	${OBJECTDIR}/src/engine/InputDriver.o \
	${OBJECTDIR}/src/engine/SignalManager.o \
	${OBJECTDIR}/src/engine/TextureManager.o \
	${OBJECTDIR}/src/engine/VideoDriver.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/screens/GameOverScreen.o \
	${OBJECTDIR}/src/screens/GameScreen.o \
	${OBJECTDIR}/src/screens/PauseScreen.o \
	${OBJECTDIR}/src/screens/Screen.o \
	${OBJECTDIR}/src/screens/StartScreen.o \
	${OBJECTDIR}/src/ui/UIBox.o \
	${OBJECTDIR}/src/ui/UIButton.o \
	${OBJECTDIR}/src/ui/UIElement.o \
	${OBJECTDIR}/src/ui/UIIcon.o \
	${OBJECTDIR}/src/ui/UILabel.o \
	${OBJECTDIR}/src/ui/UIManager.o \
	${OBJECTDIR}/src/ui/UIProgressBar.o \
	${OBJECTDIR}/src/world/Pickup.o \
	${OBJECTDIR}/src/world/WorldManager.o \
	${OBJECTDIR}/src/world/WorldMath.o \
	${OBJECTDIR}/src/world/WorldRenderManager.o


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

${OBJECTDIR}/src/characters/Gem.o: src/characters/Gem.cpp
	${MKDIR} -p ${OBJECTDIR}/src/characters
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/characters/Gem.o src/characters/Gem.cpp

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

${OBJECTDIR}/src/screens/GameOverScreen.o: src/screens/GameOverScreen.cpp
	${MKDIR} -p ${OBJECTDIR}/src/screens
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/screens/GameOverScreen.o src/screens/GameOverScreen.cpp

${OBJECTDIR}/src/screens/GameScreen.o: src/screens/GameScreen.cpp
	${MKDIR} -p ${OBJECTDIR}/src/screens
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/screens/GameScreen.o src/screens/GameScreen.cpp

${OBJECTDIR}/src/screens/PauseScreen.o: src/screens/PauseScreen.cpp
	${MKDIR} -p ${OBJECTDIR}/src/screens
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/screens/PauseScreen.o src/screens/PauseScreen.cpp

${OBJECTDIR}/src/screens/Screen.o: src/screens/Screen.cpp
	${MKDIR} -p ${OBJECTDIR}/src/screens
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/screens/Screen.o src/screens/Screen.cpp

${OBJECTDIR}/src/screens/StartScreen.o: src/screens/StartScreen.cpp
	${MKDIR} -p ${OBJECTDIR}/src/screens
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/screens/StartScreen.o src/screens/StartScreen.cpp

${OBJECTDIR}/src/ui/UIBox.o: src/ui/UIBox.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIBox.o src/ui/UIBox.cpp

${OBJECTDIR}/src/ui/UIButton.o: src/ui/UIButton.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIButton.o src/ui/UIButton.cpp

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

${OBJECTDIR}/src/ui/UIProgressBar.o: src/ui/UIProgressBar.cpp
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ui/UIProgressBar.o src/ui/UIProgressBar.cpp

${OBJECTDIR}/src/world/Pickup.o: src/world/Pickup.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/Pickup.o src/world/Pickup.cpp

${OBJECTDIR}/src/world/WorldManager.o: src/world/WorldManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/WorldManager.o src/world/WorldManager.cpp

${OBJECTDIR}/src/world/WorldMath.o: src/world/WorldMath.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/WorldMath.o src/world/WorldMath.cpp

${OBJECTDIR}/src/world/WorldRenderManager.o: src/world/WorldRenderManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world/WorldRenderManager.o src/world/WorldRenderManager.cpp

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
