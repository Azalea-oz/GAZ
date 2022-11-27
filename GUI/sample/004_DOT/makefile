.PHONY:build
build:
	g++ -c main.cpp
	g++ main.o -o main -L./ -lAZALEA -mwindows

.PHONY:debug
debug:
	g++ -c main.cpp
	g++ main.o -o main -DAZDEBUF=1 -L./ -lAZALEA -lazdebug64 -mwindows

.PHONY:clean
clean:
	rm *.o *.exe
