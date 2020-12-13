OBJS = font.o
SRC = font.cpp
HP = font.hpp

MAIN = main.cpp

RM = del

.PHONY: target
target: 
	g++ main.cpp ../GUI/gui.cpp ../WCLASS/wclass.cpp -o main -L../ -lazdebug64 -lvfw32 -mwindows

.PHONY: clean
clean:
	$(RM) *.o *.gch *.exe