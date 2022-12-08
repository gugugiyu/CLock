output: test.o basic.o
	gcc ./test.o ./basic.o -o output

test.o: ./test/test.c
	gcc -c ./test/test.c

basic.o: ./src/basic.c ./include/basic.h
	gcc -c ./src/basic.c

clean:
	rm *.o o