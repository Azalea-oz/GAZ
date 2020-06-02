DLL = azdebug32.dll
SLIB = azdebug32.lib
SRCCPP = debug.cpp
OBJS = debug.o
CXXFLAGS = -c -std=c++14
RM = del

.PHONY: dll
dll:
	g++ -shared -Wl,--kill-at debug.cpp time.cpp -o azdebug32.dll

.PHONY: lib
lib: $(OBJS)
	ar rcs $(SLIB) $(OBJS)

$(OBJS): $(SRCCPP)
	g++ -c $(SRCCPP)

.PHONY: clean
clean:
	$(RM) $(DLL) $(SLIB) *.o