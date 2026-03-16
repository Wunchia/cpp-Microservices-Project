.PHONY: all clean rebuild
all: test test2 test3
test: test.c
	gcc test.c -o test
test2: test2.c
	gcc test2.c -o test2
test3: test3.c
	gcc test3.c -o test3
clean:
	rm -f test test2 test3
rebuild: clean all
