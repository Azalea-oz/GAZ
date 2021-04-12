DLL = main.dll

SRCCPP = main.cpp
OBJS = main.o
CXXFLAGS = -c -std=c++14
RM = del


.PHONY: dll
dll: $(OBJS)
	g++ $(OBJS) -o $(DLL) -shared

$(OBJS): $(SRCCPP)
	g++ -c $(SRCCPP)

.PHONY: exe
exe:
	g++ -c test.cpp
	g++ test.o -o test main.dll

.PHONY: clean
clean:
	$(RM) $(DLL) $(SLIB) *.o *.a *.dll