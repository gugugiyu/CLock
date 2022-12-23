output: test.o basic.o BaseEncoder.o
	gcc ./test.o ./basic.o ./BaseEncoder.o -o output

test.o: ./test/test.c
	gcc -c ./test/test.c

basic.o: ./src/basic.c ./include/basic.h
	gcc -c ./src/basic.c

BaseEncoder.o: ./src/BaseEncoder.c ./include/BaseEncoder.h
	gcc -c ./src/BaseEncoder.c

clean:
	rm *.o output.exe output.exe.stackdump