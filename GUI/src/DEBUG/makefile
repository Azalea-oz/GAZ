DLL32 = azdebug32.dll
SLIB32 = azdebug32.lib

DLL64 = azdebug64.dll
SLIB64 = azdebug64.lib

SRCCPP = debug.cpp
OBJS = debug.o
CXXFLAGS = -c -std=c++14
RM = del

.PHONY: dll32
dll32:
	g++ -static -shared -o $(DLL32) $(SRCCPP) -Wl,--out-implib,libdebug.a

.PHONY: lib32
lib32: $(OBJS)
	ar rcs $(SLIB32) $(OBJS)

.PHONY: dll64
dll64:
	g++ -static -shared -o $(DLL64) $(SRCCPP) -Wl,--out-implib,libdebug.a

.PHONY: lib64
lib64: $(OBJS)
	ar rcs $(SLIB64) $(OBJS)

$(OBJS): $(SRCCPP)
	g++ -c $(SRCCPP)

.PHONY: clean
clean:
	$(RM) $(DLL) $(SLIB) *.o *.a *.dll *.lib