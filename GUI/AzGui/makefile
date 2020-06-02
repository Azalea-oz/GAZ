PROG = AZGUI
SRCCPP = testmain2.cpp gui.cpp wclass.cpp paint.cpp
CXXFLAGS = -c  -std=c++14
OBJS = $(SRCCPP:.cpp=.o)


LIBDIR = -L./
LIBS = -lcomctl32 -lgdiplus -lgdi32 -lazdebug32 -luser32 -mwindows
SLIBS = -lcomctl32 -lgdiplus -lgdi32 -luser32 -mwindows

RM = del

.PHONY: build
build: $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(LIBDIR) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

.PHONY: static
static: $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) azdebug32.lib $(LIBDIR) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

.PHONY: lib
lib: $(OBJS)
	ar rcs AZALEA.lib $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

.PHONY: build2
build2: testmain2.o
	$(CXX) -o $(PROG) testmain2.o AZALEA.lib $(LIBDIR) $(LIBS)

tastmain2.o: testmain2.cpp
	$(CXX) $(CXXFLAGS) testmain2.cpp

.PHONY: clean
clean:
	$(RM) $(PROG).exe *.d *.o