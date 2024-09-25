# makefile for lib_used array object.
lib_used: lib_used.o array.o object.o
	gcc -Wall -Wextra -Wpedantic -std=c11 lib_used.o array.o object.o -o lib_used
lib_used.o: lib_used.c
	gcc -c -Wall -Wextra -Wpedantic -std=c11 lib_used.c -o lib_used.o
array.o: array.c
	gcc -c -Wall -Wextra -Wpedantic -std=c11 array.c -o array.o
object.o: object.c
	gcc -c -Wall -Wextra -Wpedantic -std=c11 object.c -o object.o	
	
