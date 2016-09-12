TARGET = diksam
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  util.o\
  ../memory/mem.o\

CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG

INCLUDES = \
  -I/usr/local/include\
  -I../include

$(TARGET):$(OBJS)
	cd ../memory; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm -lmsvcp60

clean:
	rm -f *.o lex.yy.c y.tab.c y.output y.tab.h *~
y.tab.h : diksam.y
	bison --yacc -dv diksam.y
y.tab.c : diksam.y
	bison --yacc -dv diksam.y
lex.yy.c : diksam.l diksam.y y.tab.h
	flex diksam.l
y.tab.o: y.tab.c diksamc.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c diksamc.h ../include/MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
../memory/mem.o:
	cd ../memory; $(MAKE);
############################################################
interface.o: interface.c ../include/MEM.h diksamc.h \
 ../include/DKC.h ../include/DVM_code.h ../include/DVM.h
main.o: main.c ../include/DKC.h ../include/DVM_code.h ../include/DVM.h \
 ../include/MEM.h
util.o: util.c ../include/MEM.h diksamc.h \
 ../include/DKC.h ../include/DVM_code.h ../include/DVM.h