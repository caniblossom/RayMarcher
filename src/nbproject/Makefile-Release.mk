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
CND_PLATFORM=MinGW-i686-4.9.2-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/raymarcher/flowerpot/config/packing.o \
	${OBJECTDIR}/raymarcher/flowerpot/log/log.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glbuffer.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glerror.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glframebuffer.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glprogram.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glshader.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture2d.o \
	${OBJECTDIR}/raymarcher/flowerpot/opengl/glvertexarray.o \
	${OBJECTDIR}/raymarcher/flowerpot/surface/lodepng/lodepng.o \
	${OBJECTDIR}/raymarcher/flowerpot/surface/surface.o \
	${OBJECTDIR}/raymarcher/flowerpot/system/sdl.o \
	${OBJECTDIR}/raymarcher/flowerpot/system/systemlog.o \
	${OBJECTDIR}/raymarcher/flowerpot/window/window.o \
	${OBJECTDIR}/raymarcher/flowerpot/window/windowmanager.o \
	${OBJECTDIR}/raymarcher/interface/mainwindow.o \
	${OBJECTDIR}/raymarcher/interface/surfacerenderer.o \
	${OBJECTDIR}/raymarcher/main.o \
	${OBJECTDIR}/raymarcher/object/scene.o \
	${OBJECTDIR}/raymarcher/renderer/camera.o \
	${OBJECTDIR}/raymarcher/renderer/image.o \
	${OBJECTDIR}/raymarcher/renderer/rgen.o \
	${OBJECTDIR}/raymarcher/renderer/tracer.o


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
LDLIBSOPTIONS=-L../../../msys/lib -lmingw32 -lSDL2main -lglew32.dll -lopengl32 -lSDL2.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raymarcher.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raymarcher.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raymarcher ${OBJECTFILES} ${LDLIBSOPTIONS} -mwindows

${OBJECTDIR}/raymarcher/flowerpot/config/packing.o: raymarcher/flowerpot/config/packing.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/config/packing.o raymarcher/flowerpot/config/packing.cpp

${OBJECTDIR}/raymarcher/flowerpot/log/log.o: raymarcher/flowerpot/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/log
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/log/log.o raymarcher/flowerpot/log/log.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glbuffer.o: raymarcher/flowerpot/opengl/glbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glbuffer.o raymarcher/flowerpot/opengl/glbuffer.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glerror.o: raymarcher/flowerpot/opengl/glerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glerror.o raymarcher/flowerpot/opengl/glerror.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glframebuffer.o: raymarcher/flowerpot/opengl/glframebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glframebuffer.o raymarcher/flowerpot/opengl/glframebuffer.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glprogram.o: raymarcher/flowerpot/opengl/glprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glprogram.o raymarcher/flowerpot/opengl/glprogram.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glshader.o: raymarcher/flowerpot/opengl/glshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glshader.o raymarcher/flowerpot/opengl/glshader.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture.o: raymarcher/flowerpot/opengl/gltexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture.o raymarcher/flowerpot/opengl/gltexture.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture2d.o: raymarcher/flowerpot/opengl/gltexture2d.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/gltexture2d.o raymarcher/flowerpot/opengl/gltexture2d.cpp

${OBJECTDIR}/raymarcher/flowerpot/opengl/glvertexarray.o: raymarcher/flowerpot/opengl/glvertexarray.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/opengl/glvertexarray.o raymarcher/flowerpot/opengl/glvertexarray.cpp

${OBJECTDIR}/raymarcher/flowerpot/surface/lodepng/lodepng.o: raymarcher/flowerpot/surface/lodepng/lodepng.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/surface/lodepng
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/surface/lodepng/lodepng.o raymarcher/flowerpot/surface/lodepng/lodepng.cpp

${OBJECTDIR}/raymarcher/flowerpot/surface/surface.o: raymarcher/flowerpot/surface/surface.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/surface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/surface/surface.o raymarcher/flowerpot/surface/surface.cpp

${OBJECTDIR}/raymarcher/flowerpot/system/sdl.o: raymarcher/flowerpot/system/sdl.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/system/sdl.o raymarcher/flowerpot/system/sdl.cpp

${OBJECTDIR}/raymarcher/flowerpot/system/systemlog.o: raymarcher/flowerpot/system/systemlog.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/system/systemlog.o raymarcher/flowerpot/system/systemlog.cpp

${OBJECTDIR}/raymarcher/flowerpot/window/window.o: raymarcher/flowerpot/window/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/window
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/window/window.o raymarcher/flowerpot/window/window.cpp

${OBJECTDIR}/raymarcher/flowerpot/window/windowmanager.o: raymarcher/flowerpot/window/windowmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/flowerpot/window
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/flowerpot/window/windowmanager.o raymarcher/flowerpot/window/windowmanager.cpp

${OBJECTDIR}/raymarcher/interface/mainwindow.o: raymarcher/interface/mainwindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/interface/mainwindow.o raymarcher/interface/mainwindow.cpp

${OBJECTDIR}/raymarcher/interface/surfacerenderer.o: raymarcher/interface/surfacerenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/interface/surfacerenderer.o raymarcher/interface/surfacerenderer.cpp

${OBJECTDIR}/raymarcher/main.o: raymarcher/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/main.o raymarcher/main.cpp

${OBJECTDIR}/raymarcher/object/scene.o: raymarcher/object/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/object
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/object/scene.o raymarcher/object/scene.cpp

${OBJECTDIR}/raymarcher/renderer/camera.o: raymarcher/renderer/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/renderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/renderer/camera.o raymarcher/renderer/camera.cpp

${OBJECTDIR}/raymarcher/renderer/image.o: raymarcher/renderer/image.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/renderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/renderer/image.o raymarcher/renderer/image.cpp

${OBJECTDIR}/raymarcher/renderer/rgen.o: raymarcher/renderer/rgen.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/renderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/renderer/rgen.o raymarcher/renderer/rgen.cpp

${OBJECTDIR}/raymarcher/renderer/tracer.o: raymarcher/renderer/tracer.cpp 
	${MKDIR} -p ${OBJECTDIR}/raymarcher/renderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../msys/include -Iraymarcher -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raymarcher/renderer/tracer.o raymarcher/renderer/tracer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raymarcher.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
