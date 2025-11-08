all: snake.o ListaDinamicaEncadeada.o
	gcc snake.o ListaDinamicaEncadeada.o -o TrabProgII -lm -lraylib

snake.o: snake.c snake.h
	gcc -c snake.c

ListaDinamicaEncadeada.o: ListaDinamicaEncadeada.c ListaDinamicaEncadeada.h
	gcc -c ListaDinamicaEncadeada.c

clean:
	rm -f TrabProgII *.o

run:
	./TrabProgII
