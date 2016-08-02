TARGET = Yap
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  create.o\
  util.o\
  native.o\
  ./memory/mem.o
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	cd ./memory; $(MAKE);
	$(CC) $(OBJS) -o Yap -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.output y.tab.h *~
y.tab.h : yap.y
	bison --yacc -dv yap.y
y.tab.c : yap.y
	bison --yacc -dv yap.y
lex.yy.c : yap.l yap.y y.tab.h
	flex yap.l
y.tab.o: y.tab.c yaplang.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c yaplang.h
	$(CC) -c -g $*.c $(INCLUDES)
main.o: main.c
	$(CC) -c -g $*.c $(INCLUDES)
interface: interface.c
	$(CC) -c -g $*.c $(INCLUDES)
create: create.c
	$(CC) -c -g $*.c $(INCLUDES)
util: util.c
	$(CC) -c -g $*.c $(INCLUDES)
native.o: native.c
	$(CC) -c -g $*.c $(INCLUDES)