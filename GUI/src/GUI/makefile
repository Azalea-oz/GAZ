OBJS = gui.o
SRC = gui.cpp
HPP = gui.hpp

RM = del

.PHONY: obj
obj: $(SRC) $(HPP)
	g++ -c $(SRC) $(HPP) -std=c++17

.PHONY: clean
clean:
	$(RM) *.o *.gch

.PHONY: Build
Build: gui.o event.o
	makedepend

.PHONY: BuildA
BuildA: gui.cpp gui.hpp
	g++ -c gui.cpp gui.hpp -std=c++17

.PHONY: BuildB
BuildB: event.cpp event.hpp
	g++ -c event.cpp event.hpp -std=c++17


