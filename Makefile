CC=gcc
CFLAGS=-Wall -O0 -g
TARGET=bin
PROGRAMNAME=bin/test

OBJ= rbtree.o RbtreeTest.o

all: test
rbtree.o: rbtree.c
RbtreeTest.o: RbtreeTest.c

test: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROGRAMNAME) $(CFLAGS) $(OBJ)
	find . -name "*.o"|xargs rm -rf
clean:
	rm -rf *.o $(TARGET)/* 
