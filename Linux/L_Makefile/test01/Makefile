main: add.o main.o
	gcc add.o main.o -o main
add.o: add.c compute.h
	gcc -c add.c -o add.o -Wall -g
main.o: main.c compute.h
	gcc -c main.c -o main.o -Wall -g
