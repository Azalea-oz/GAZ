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


PROG = AZGUI
PROGSJIS = AZGUISJIS
SRCCPP = testmain2.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp EVENT/event.cpp
SRCCPPSJIS = testmain2.cpp GUI/gui.cpp WCLASS/wclass.cpp PAINT/paint.cpp
CXXFLAGS = -c -std=c++14
OBJS = $(SRCCPP:.cpp=.o)
LIBDIR = -L./

#######################################################################


LIBS32 = -lcomctl32 -lgdiplus -lgdi32 -l../DEBUG/azdebug32 -luser32 -limm32 -mwindows

.PHONY: build32-exe
build32-exe: $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(LIBDIR) $(LIBS32)

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)


#######################################################################


LIBS64 = -lcomctl32 -lgdiplus -lgdi32 -l../DEBUG/azdebug64 -luser32 -limm32 -mwindows

.PHONY: build64-exe
build64-exe: $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(LIBDIR) $(LIBS64)

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)


#######################################################################


LIBS64 = -lcomctl32 -lgdiplus -lgdi32 -l../DEBUG/azdebug64 -luser32 -limm32 -mwindows

.PHONY: build64-exe-g
build64-exe-g: $(OBJS)
	$(CXX) -g -O0 -o $(PROG) $(OBJS) $(LIBDIR) $(LIBS64)

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)


#######################################################################

LIBS32 = -lcomctl32 -lgdiplus -lgdi32 -l../DEBUG/azdebug32 -luser32 -limm32 -mwindows

.PHONY: build32-exe-sjis
build32-exe-sjis: $(OBJS)
	$(CXX) -o $(PROGSJIS) $(OBJS) $(LIBDIR) $(LIBS32)

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)


#######################################################################


LIBS64 = -lcomctl32 -lgdiplus -lgdi32 -l../DEBUG/azdebug64 -luser32 -ldwmapi -limm32 -mwindows

.PHONY: build64-exe-sjis
build64-exe-sjis: $(OBJS)
	$(CXX) -o $(PROGSJIS) $(OBJS) $(LIBDIR) $(LIBS64)

%.o: %.cpp %.hpp
	cd $(dir $(abspath $<)) && $(CXX) $(CXXFLAGS) $(notdir $<)


#######################################################################

DLL = AZALEA.dll
DLLOP = -Wl,--out-implib,$(DLL:.dll=.a)

.PHONY: dll
dll:
	g++ -static -shared -o $(DLL) $(SRCCPP) $(DLLOP) $(LIBDIR) $(LIBS)


#######################################################################


LIB = AZALEA.lib

.PHONY: lib
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)


#######################################################################


RM = del

.PHONY: clean
clean:
	$(RM) $(PROG).exe *.d *.o *.gch $(DLL) $(LIB)


#######################################################################


.PHONY: clean-all
clean-all:
	$(RM) /S $(PROG).exe *.d *.o *.gch $(DLL) $(LIB)


#######################################################################