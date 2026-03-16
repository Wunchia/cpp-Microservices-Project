main: main.o add.o subtract.o
	gcc main.o add.o subtract.o -o main
main.o: main.c
	gcc -c main.c -o main.o
add.o: add.c
	gcc -c add.c -o add.o
subtract.o: subtract.c
	gcc -c subtract.c -o subtract.o
.PHONY: clean rebuild
clean:
	rm -f main main.o add.o subtract.o
rebuild:clean main
