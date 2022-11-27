DLL32 = azdebug32.dll
SLIB32 = azdebug32.lib

DLL64 = azdebug64.dll
SLIB64 = azdebug64.lib

SRCCPP = debug.cpp util.cpp
OBJS = $(SRCCPP:.cpp=.o)
CXXFLAGS = -c
STDC++ = -std=c++14
RM = del

.PHONY: help
help:
	@echo make dll32
	@echo make dll64
	@echo make lib32
	@echo make lib64
	@echo make clean

LIBS32D =
LIBS32S = -static -lstdc++ -lgcc -lwinpthread
LIBS64D =
LIBS64S = -static -lstdc++ -lgcc -lwinpthread

.PHONY: dll32
dll32: $(OBJS)
	g++ -o $(DLL32) $(OBJS) -shared -Wl,--out-implib,libdebug.lib $(LIBS32S) $(STDC++)

.PHONY: dll64
dll64: $(OBJS)
	g++ -o $(DLL64) $(OBJS) -shared -Wl,--out-implib,azdebug64.lib $(LIBS64S) $(STDC++)

.PHONY: lib32
lib32: $(OBJS)
	ar rcs $(SLIB32) $(OBJS) $(LIBS32S) $(STDC++)

.PHONY: lib64
lib64: $(OBJS)
	ar rcs $(SLIB64) $(OBJS) $(LIBS64S) $(STDC++)

$(OBJS): $(SRCCPP)
	g++ $(CXXFLAGS) $(SRCCPP) $(STDC++)

.PHONY: clean
clean:
	$(RM) $(DLL) $(SLIB) *.o *.a *.dll *.lib

.PHONY: CPYLIB
CPYLIB:
	copy *.lib ..\bin\

.PHONY: CPYDLL
CPYDLL:
	copy *.dll ..\bin\

.PHONY: CPY
CPY:
	copy *.dll ..\bin
	copy *.lib ..\bin
