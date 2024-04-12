CFLAGS=-std=c11 -g -static

ccomp: ccomp.c

test: ccomp 
	./test.sh

clean:
	rm -f ccomp *.o *~ tmp*

.PHONY: test clean
