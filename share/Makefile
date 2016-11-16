TARGET = share.o
CC = gcc
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG ../include
OBJS = wchar.o

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)
clean:
	rm -f *.o
.c.o:
	$(CC) $(CFLAGS) -I ../include $*.c
wchar.o: wchar.c ../include/MEM.h ../include/DVM.h
