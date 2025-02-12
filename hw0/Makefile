all: matrix.x clean
matrices.o : matrices.cpp
	g++ -c matrices.cpp

matrix.x : matrices.o
	g++ matrices.o -o matrix.x

clean : 
	rm matrices.o
