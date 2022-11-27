



.PHONY: Build
Build:
	g++ -c main.cpp
	g++ main.cpp -o main -mwindows -L./ -lAZALEA -lwinmm -O3

.PHONY: debug
debug:
	g++ -c main.cpp -DAZ_DEBUG=1
	g++ -g -O0 -o main main.o -mwindows -L./ -lAZALEAD -lazdebug64 -DAZ_DEBUG=1

.PHONY: UPDATE
UPDATE:
	copy ..\000_template\*.dll .
	copy ..\000_template\*.lib .
