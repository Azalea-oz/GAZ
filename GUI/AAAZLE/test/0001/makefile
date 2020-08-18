PROG = TestGUI
SRCCPP = main.cpp class.cpp
CXXFLAGS = -c -std=c++14
OBJS = $(SRCCPP:.cpp=.o)
LIBS = -lcomctl32 -lgdiplus -lgdi32 -luser32 -mwindows
RM = del

.PHONY: build
build: $(OBJS)
	$(CXX) -o $(PROG) $(OBJS)  $(LIBS) AZALEA.lib azdebug64.lib

.cpp.o:
	$(CXX) $(CXXFLAGS) $<

.PHONY: clean
clean:
	$(RM) $(PROG).exe $(OBJS)