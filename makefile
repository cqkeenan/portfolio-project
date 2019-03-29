all: main

main: main.o movie.o scanner.o
	gcc main.o movie.o scanner.o -o main

main.o: main.c
	gcc -c -Wall main.c

movie.o: movie.c
	gcc -c -Wall movie.c

scanner.o: scanner.c
	gcc -c -Wall scanner.c

clean:
	rm *o main
