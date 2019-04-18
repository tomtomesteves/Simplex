CC=g++
CFLAGS=-std=c++17

simplex: main.cpp
	$(CC) -o simplex main.cpp $(CFLAGS)

clean:
	rm -f simplex
