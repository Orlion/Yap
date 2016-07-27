#!/bin/bash
yacc -dv yap.y
lex yap.l
gcc -o yap y.tab.c lex.yy.c
