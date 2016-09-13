TARGET = mem.o
CC=gcc
CFLAGS = -c -g -DDEBUG -Wall
OBJS = memory.o storage.o

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -I../include $*.c
clean:
	rm -f *.o
memory.o: memory.c memory.h ../include/MEM.h
storage.o: storage.c memory.h ../include/MEM.h