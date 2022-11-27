



.PHONY: Build
Build:
	g++ -c main.cpp
	g++ main.o -o main -static -lstdc++ -lgcc -lwinpthread -L./ -Wl,-Bdynamic -lAZALEA -lwinmm -mwindows -O3

.PHONY: debug
debug:
	g++ -c main.cpp -DAZ_DEBUG=1
	g++ -g -O0 -o main main.o -static -lstdc++ -lgcc -lwinpthread -L./ -Wl,-Bdynamic -lAZALEAD -lazdebug64 -DAZ_DEBUG=1 -mwindows 

.PHONY: UPDATE
UPDATE:
	copy ..\sample\000_template .\