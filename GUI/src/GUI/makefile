OBJS = gui.o
SRC = gui.cpp
HPP = gui.hpp

RM = del

.PHONY: obj
obj: $(SRC)
	g++ -c $(SRC) $(HPP) -std=c++17

.PHONY: clean
clean:
	$(RM) *.o *.gch