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
	@echo make del
	@echo make clean-all
	
	@echo make first


#######################################################################


PROG = ../bin/AZGUI
PROGSJIS = ../bin/AZGUISJIS
SRCCPP = GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp EVENT/event.cpp
SRCCPPSJIS = testmain2.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp
CXXFLAGS = -c -std=c++14
OBJS = $(SRCCPP:.cpp=.o)
LIBDIR = -L../DEBUG

DLL = ../bin/AZALEA.dll

## build import library from dynamic library
DLLOP = -Wl,--out-implib,$(DLL:.dll=.lib)

LIB = ../bin/AZALEA.lib

LIBS32 = -static -lcomctl32 -lgdiplus -lgdi32 -luser32 -lstdc++ -lgcc -lwinpthread
LIBS64 = -static -lcomctl32 -lgdiplus -lgdi32 -luser32 -lstdc++ -lgcc -lwinpthread

LIBSDEBUG = -lazdebug64
BUILDFLAGS = -mwindows
DEBUGFLAGS = -g -O0

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)

RM = del

#######################################################################

.PHONY: build32-exe
build32-exe: $(OBJS)
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) testmain2.o $(OBJS) $(LIBDIR) $(LIBS32) $(BUILDFLAGS)

#######################################################################

.PHONY:build64-exe
build64-exe: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp
	$(CXX) -o $(PROG) testmain2.o $(OBJS) $(LIBDIR) $(LIBSDEBUG) $(LIBS64) $(BUILDFLAGS)

../bin/azdebug64.dll:
	cd ../DEBUG && mingw32-make dll64 && mingw32-make dll64D
	copy ..\DEBUG\azdebug64.dll ..\bin\azdebug64.dll

#######################################################################

.PHONY: build64-exe-g
build64-exe-g: $(OBJS) ../bin/azdebug64.dll
	g++ -c testmain2.cpp
	$(CXX) $(DEBUGFLAGS) -o $(PROG) testmain2.o $(OBJS) $(LIBDIR) $(LIBSDEBUG) $(LIBS64) $(BUILDFLAGS)

#######################################################################

.PHONY: dll
dll:$(OBJS)
	g++ $(OBJS) -o $(DLL) -shared $(DLLOP) $(LIBDIR) $(LIBSDEBUG) $(LIBS64)

#######################################################################

.PHONY: lib
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)

#######################################################################

.PHONY: clean
clean:
	$(RM) ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################

.PHONY: clean-all
clean-all:
	$(RM) /S ..\bin\*.exe *.d *.o *.gch ..\bin\*.dll ..\bin\*.lib

#######################################################################