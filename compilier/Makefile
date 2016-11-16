TARGET = diksam
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  create.o\
  string.o\
  util.o\
  ../memory/mem.o\
  ../share/share.o

CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG -DSHIFT_JIS_SOURCE

INCLUDES = \
  -I/usr/local/include\
  -I../include

$(TARGET):$(OBJS)
	cd ../share; $(MAKE);
	cd ../memory; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm

clean:
	rm -f *.o lex.yy.c y.tab.c y.output y.tab.h *~;
	cd ../memory; $(MAKE) clean;
	cd ../share; $(MAKE) clean;
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
../share/share.o:
	cd ../share; $(MAKE);
############################################################
create.o: create.c ../include/MEM.h diksamc.h
interface.o: interface.c ../include/MEM.h diksamc.h \
 ../include/DKC.h ../include/DVM_code.h ../include/DVM.h
main.o: main.c ../include/DKC.h ../include/DVM_code.h ../include/DVM.h \
 ../include/MEM.h
 string.o: string.c ../include/MEM.h diksamc.h ../include/DKC.h ../include/DVM_code.h ../include/share.h
util.o: util.c ../include/MEM.h diksamc.h \
 ../include/DKC.h ../include/DVM_code.h ../include/DVM.h
 