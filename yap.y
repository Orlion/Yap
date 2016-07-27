%{
#include <stdio.h>
#include <stdlib.h>	
#define YYDEBUG 1
%}
%union{
	 
}
%token FUNCTION IF ELSE ELSEIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T
        LP RP LC RC SEMICOLON COMMA ASSIGN LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T GLOBAL_T
%%
line_list
    : line
    | line_list line
    ;
line
    : expression
    {
        
    }
expression
    : term
    | expression ADD term
    {
        
    }
    | expression SUB term
    {
        
    }
    ;
term
    : primary_expression
    | term MUL primary_expression 
    {
        
    }
    | term DIV primary_expression
    {
        
    }
    ;
primary_expression
	: DIV
	{

	}
    ;
%%
int yyerror(char const *str)
{
	extern char *yytext;
	fprintf(stderr, "parse error near %s\n", yytext);
	return 0;
}