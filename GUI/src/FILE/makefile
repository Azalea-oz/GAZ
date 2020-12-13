SRCCPP = event.cpp
OBJS = $(SRCCPP:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

.PHONY: clean
clean:
	$(RM) $(PROG).exe $(OBJS)