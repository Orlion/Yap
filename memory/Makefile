TARGET = mem.o
CC=gcc
CFLAGS = -c -g -DDEBUG -Wall
OBJS = storage.o

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
clean:
	rm -f *.o
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c
storage.o: storage.c ../include/MEM.h
