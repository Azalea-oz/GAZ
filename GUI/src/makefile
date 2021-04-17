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
	@echo make dll
	@echo make lib
	@echo make debug
	@echo make del
	@echo make clean-all
	
	@echo make first


#######################################################################


PROG = ../bin/AZGUI
PROGSJIS = ../bin/AZGUISJIS
SRCCPP = UTIL/utility.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp EVENT/event.cpp
SRCCPPSJIS = testmain2.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp
CXXFLAGS = -c -std=c++14
OBJS = $(SRCCPP:.cpp=.o)
LIBDIR = -L../DEBUG

DLL = ../bin/AZALEA.dll
DEBUGDLL = ../bin/AZALEAD.dll

## build import library from dynamic library
DLLOP = -Wl,--out-implib,$(DLL:.dll=.lib)
DEBUGDLLOP = -Wl,--out-implib,$(DEBUGDLL:.dll=.lib)

LIB = ../bin/AZALEA.lib

LIBS32D = -lcomctl32 -lgdiplus -lgdi32 -luser32 -lwinmm
LIBS32S = -static -lstdc++ -lgcc
LIBS64D = -lcomctl32 -lgdiplus -lgdi32 -luser32 -lwinmm
LIBS64S = -static -lstdc++ -lgcc

LIBSDEBUG = -lazdebug64
BUILDFLAGS = -mwindows
DEBUGFLAGS = -g -O0

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<) -O3
##cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<) -DAZ_DEBUG=1

RM = del

#######################################################################

.PHONY: build32-exe
build32-exe: $(OBJS)
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) $(OBJS) testmain2.o $(LIBDIR) $(LIBS32D) $(LIBS32S) $(BUILDFLAGS)

#######################################################################

.PHONY:build64-exe
build64-exe: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) $(OBJS) testmain2.o $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(LIBS64S) $(BUILDFLAGS)

../bin/azdebug64.dll:
	cd ../DEBUG && mingw32-make dll64 && mingw32-make lib64 && mingw32-make dll64
	copy ..\DEBUG\azdebug64.dll ..\bin\azdebug64.dll

#######################################################################

.PHONY: build64-exe-g-nolib
build64-exe-g-nolib: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp -DAZ_DEBUG=1
	$(CXX) $(DEBUGFLAGS) -o $(PROG) testmain2.o $(OBJS) $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(LIBS64S) $(BUILDFLAGS) -DAZ_DEBUG=1

#######################################################################

.PHONY: build64-exe-g
build64-exe-g: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp -DAZ_DEBUG=1
	$(CXX) $(DEBUGFLAGS) -o $(PROG) testmain2.o $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(LIBS64S) -L../bin -lAZALEAD $(BUILDFLAGS) -DAZ_DEBUG=1


#######################################################################

.PHONY: dll
dll: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBS64D) $(LIBS64S) -O3

#######################################################################

.PHONY: lib
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)

#######################################################################

.PHONY: debug
debug: $(OBJS)
	g++ $(OBJS) -o $(DEBUGDLL) -shared $(DEBUGDLLOP) $(LIBDIR) $(LIBSDEBUG) $(LIBS64D) $(LIBS64S) -DAZ_DEBUG=1

#######################################################################

.PHONY: clean
clean:
	$(RM) ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################

.PHONY: clean-o
clean-o:
	$(RM) /S *.d *.o *.gch

#######################################################################

.PHONY: clean-all
clean-all:
	$(RM) /S ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################