PROG = main
SRCCPP = main.cpp
CXXFLAGS = -c -std=c++14
OBJS = $(SRCCPP:.cpp=.o)

.PHONY: build
build: $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) -mwindows -L../../ -lAZALEA -lazdebug64

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

.PHONY: clean
clean:
	del *.o *.exe 
