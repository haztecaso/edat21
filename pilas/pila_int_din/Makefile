CC=g++

main: main.cpp pila_int.o
	$(CC) -o main main.cpp pila_int.o

pila_int.o: pila_int.cpp pila_int.hpp
	$(CC) -c pila_int.cpp 

clean:
	rm main pila_int.o
