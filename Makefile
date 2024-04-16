CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

ccomp: $(OBJS)
		$(CC) -o ccomp $(OBJS) $(LDFLAGS)

$(OBJS): ccomp.h

test: ccomp 
	./test.sh

clean:
	rm -f ccomp *.o *~ tmp*

.PHONY: test clean
