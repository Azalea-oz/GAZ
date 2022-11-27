#######################################################################
### tempalte makefile
### 2020/06/29
### author : Azalea
#######################################################################


#######################################################################


.PHONY: help
help:
	@echo make build32-exe
	@echo make build64-exe
	@echo.
	@echo make dll
	@echo make lib
	@echo.
	@echo make debug
	@echo.
	@echo make clean-bin
	@echo make clean-obj
	@echo make clean-all
	
	@echo make BUILD


#######################################################################


PROG = ../bin/AZGUI
PROGSJIS = ../bin/AZGUISJIS

SRCCPP = UTIL/utility.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp EVENT/event.cpp
SRCCPPSJIS = testmain2.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp

CXXFLAGS = -c -std=c++14
MAKE64 = mingw32-make.exe

OBJS = $(SRCCPP:.cpp=.o)

LIBDIR = -L../DEBUG

DLL = $(if $(DEBUGOP),\
		../bin/AZALEAD.dll,\
		../bin/AZALEA.dll)

comma:=,

## build import library from dynamic library
DLLOP = $(if $(DEBUGOP),\
		-Wl$(comma)--out-implib$(comma)../bin/AZALEAD.lib,\
		-Wl$(comma)--out-implib$(comma)../bin/AZALEA.lib)

LIB = ../bin/AZALEA.lib

LIBS32D = -Wl,-Bdynamic -lcomctl32 -lgdiplus -lgdi32 -luser32 -lwinmm
LIBS32S = -static -lstdc++ -lgcc -lwinpthread
LIBS64D = -Wl,-Bdynamic -lcomctl32 -lgdiplus -lgdi32 -luser32 -lwinmm
LIBS64S = -static -lstdc++ -lgcc -lwinpthread

LIBSDEBUG = -lazdebug64
BUILDFLAGS = -mwindows
DEBUGFLAGS = -g -O0

%.o: %.cpp %.hpp
	$(if $(DEBUGOP),\
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<) $(DEBUGOP),\
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<) -O3)

RM = del

../bin/azdebug64.dll:
	cd ../DEBUG && $(MAKE64) dll64 && $(MAKE64) CPY




#######################################################################

.PHONY: build32-exe
build32-exe: init $(OBJS)
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) $(OBJS) testmain2.o $(LIBDIR) $(LIBS32D) $(LIBS32S) $(BUILDFLAGS)
init:
	$(MAKE64) clean-all

#######################################################################

.PHONY:build64-exe
build64-exe: init $(OBJS)
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) $(OBJS) testmain2.o $(LIBS64S) $(LIBDIR) $(LIBS64D) $(BUILDFLAGS)

#######################################################################

.PHONY: build64-exe-g-nolib
build64-exe-g-nolib: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp -DAZ_DEBUG=1
	$(CXX) $(DEBUGFLAGS) -o $(PROG) testmain2.o $(OBJS) $(LIBS64S) $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(BUILDFLAGS) -DAZ_DEBUG=1

#######################################################################

.PHONY: build64-exe-g
build64-exe-g:DEBUGOP:=-DAZ_DEBUG=1
build64-exe-g: init $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp -DAZ_DEBUG=1
	$(CXX) $(DEBUGFLAGS) -o $(PROG) $(OBJS) testmain2.o $(LIBS64S) $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(BUILDFLAGS) -DAZ_DEBUG=1


#######################################################################

.PHONY:build64-exe-unicode
build64-exe-unicode: init $(OBJS)
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) $(OBJS) testmain2.o $(LIBS64S) $(LIBDIR) $(LIBS64D) $(BUILDFLAGS)

#######################################################################

.PHONY: dll
dll:DEBUGOP:=
dll: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBS64S) $(LIBS64D) -O3

#######################################################################

.PHONY: dlltest
dlltest:DEBUGOP:=
dlltest: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBS64D) -lstdc++ -lgcc -O3

#######################################################################

.PHONY: dllD
dllD:DEBUGOP:=-DAZ_DEBUG=1
dllD: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBS64S) $(LIBS64D) $(LIBSDEBUG) $(DEBUGOP)

#######################################################################

.PHONY: lib
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)

#######################################################################

.PHONY: debug
debug:DEBUGOP:=-DAZ_DEBUG=1
debug: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBSDEBUG) $(LIBS64S) $(LIBS64D) $(DEBUGOP)

#######################################################################

.PHONY: clean
clean:
	@$(RM) ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################

.PHONY: clean-bin
clean-bin:
	@$(RM) ..\bin\*.exe ..\bin\*.dll ..\bin\*.lib

#######################################################################

.PHONY: clean-obj
clean-obj:
	@$(RM) /S *.d *.o *.gch

#######################################################################

.PHONY: clean-all
clean-all:
	@$(RM) /S ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################

.PHONY: BUILD
BUILD:
	$(MAKE64) clean-all && $(MAKE64) dll  && copy ..\bin ..\sample\000_template
	cd ../DEBUG && $(MAKE64) dll64 && $(MAKE64) CPY
	$(MAKE64) clean-obj && $(MAKE64) dllD && copy ..\bin ..\sample\000_template

#######################################################################