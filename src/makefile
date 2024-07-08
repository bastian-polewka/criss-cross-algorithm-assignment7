main: main.o mul.o
	g++ main.o mul.o -o main

main.o: main.cpp mul.h
	g++ -c main.cpp -std=c++20

mul.o: mul.cpp mul.h
	g++ -c mul.cpp -std=c++20

clean:
	rm -f main main.o mul.o