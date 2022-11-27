



.PHONY: Build
Build:
	g++ -c main.cpp
	g++ main.o -o main -L./ -lAZALEA -lwinmm -lgdi32 -O3 -DAZ_TEST_DEBUG=1
.PHONY: debug
debug:
	g++ -c main.cpp -DAZ_DEBUG=1
	g++ -g -O0 -o main main.o -mwindows -L./ -lAZALEAD -lazdebug64 -DAZ_DEBUG=1
