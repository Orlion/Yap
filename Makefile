TARGET = yap
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  create.o\
  execute.o\
  eval.o\
  string.o\
  string_pool.o\
  util.o\
  native.o\
  error.o\
  error_message.o\
  ./memory/mem.o
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	cd ./memory; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
y.tab.h : yap.y
	bison --yacc -dv yap.y
y.tab.c : yap.y
	bison --yacc -dv yap.y
lex.yy.c : yap.l yap.y y.tab.h
	flex yap.l
y.tab.o: y.tab.c yaplang.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c yaplang.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
./memory/mem.o:
	cd ./memory; $(MAKE);
############################################################
create.o: create.c MEM.h yaplang.h YAP.h YAP_dev.h
error.o: error.c MEM.h yaplang.h YAP.h YAP_dev.h
error_message.o: error_message.c yaplang.h MEM.h YAP.h YAP_dev.h
eval.o: eval.c MEM.h yaplang.h YAP.h YAP_dev.h
execute.o: execute.c MEM.h yaplang.h YAP.h YAP_dev.h
interface.o: interface.c MEM.h yaplang.h YAP.h YAP_dev.h
main.o: main.c YAP.h MEM.h
native.o: native.c MEM.h yaplang.h YAP.h YAP_dev.h
string.o: string.c MEM.h yaplang.h YAP.h YAP_dev.h
string_pool.o: string_pool.c MEM.h yaplang.h YAP.h YAP_dev.h
util.o: util.c MEM.h yaplang.h YAP.h YAP_dev.h
