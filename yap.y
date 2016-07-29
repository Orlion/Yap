%{
#include <stdio.h>
#include <stdlib.h>	
#include "yap.h"
#define YYDEBUG 1
%}
%union {
    char                *identifier;        /* 标识符 */
    ParameterList       *parameter_list;    /* 形参列表 */
    ArgumentList        *argument_list;     /* 实参列表 */
    Expression          *expression;        /* 表达式 */
    Statement           *statement;         /* 语句 */
    StatementList       *statement_list;    /* 语句列表 */
    Block               *block;             /* 语句块 */
    Elseif               *elseif;           /* elseif */
    IdentifierList      *identifier_list;   /* 标识符列表 */
}
%{
    /* expression_opt */
%}
%token <expression>     INT_LITERAL
%token <expression>     DOUBLE_LITERAL
%token <expression>     STRING_LITERAL
%token <identifier>     IDENTIFIER
%token FUNCTION IF ELSE ELSEIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T
        LP RP LC RC SEMICOLON COMMA ASSIGN LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T GLOBAL_T
%type   <parameter_list> parameter_list
%type   <argument_list> argument_list
%type   <expression> expression expression_opt
        logical_and_expression logical_or_expression
        equality_expression relational_expression
        additive_expression multiplicative_expression
        unary_expression primary_expression
%type   <statement> statement global_statement
        if_statement while_statement for_statement
        return_statement break_statement continue_statement
%type   <statement_list> statement_list
%type   <block> block
%type   <elseif> elseif elseif_list
%type   <identifier_list> identifier_list
%%
translation_unit
        : definition_or_statement
        | translation_unit definition_or_statement
        ;
definition_or_statement
        : function_definition
        | statement
        {
            /* CRB_Interpreter *inter = crb_get_current_interpreter(); */

            /* inter->statement_list = crb_chain_statement_list(inter->statement_list, $1); */
        }
        ;
function_definition
        : FUNCTION IDENTIFIER LP parameter_list RP block
        {
            /* 函数定义 function abc(def, ghi) {} */
            /* crb_function_define($2, $4, $6); */
        }
        | FUNCTION IDENTIFIER LP RP block
        {
            /* crb_function_define($2, NULL, $5); */
        }
        ;
parameter_list
        : IDENTIFIER
        {
            /* $$ = crb_create_parameter($1); */
        }
        | parameter_list COMMA IDENTIFIER
        {
            /* $$ = crb_chain_parameter($1, $3); */
        }
        ;
argument_list
        : expression
        {
            /* $$ = crb_create_argument_list($1); */
        }
        | argument_list COMMA expression
        {
            /* $$ = crb_chain_argument_list($1, $3); */
        }
        ;
statement_list
        : statement
        {
            /* $$ = crb_create_statement_list($1); */
        }
        | statement_list statement
        {
            /* $$ = crb_chain_statement_list($1, $2); */
        }
        ;
expression
        : logical_or_expression
        | IDENTIFIER ASSIGN expression
        {
            /* a || b */
            /* a = a || b */
            /* $$ = crb_create_assign_expression($1, $3); */
        }
        ;
logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGICAL_OR logical_and_expression
        {
            /* $$ = crb_create_binary_expression(LOGICAL_OR_EXPRESSION, $1, $3); */
        }
        ;
logical_and_expression
        : equality_expression
        | logical_and_expression LOGICAL_AND equality_expression
        {
            /* $$ = crb_create_binary_expression(LOGICAL_AND_EXPRESSION, $1, $3); */
        }
        ;
equality_expression
        : relational_expression
        | equality_expression EQ relational_expression
        {
            /* $$ = crb_create_binary_expression(EQ_EXPRESSION, $1, $3); */
        }
        | equality_expression NE relational_expression
        {
            /* $$ = crb_create_binary_expression(NE_EXPRESSION, $1, $3); */
        }
        ;
relational_expression
        : additive_expression
        | relational_expression GT additive_expression
        {
            /* $$ = crb_create_binary_expression(GT_EXPRESSION, $1, $3); */
        }
        | relational_expression GE additive_expression
        {
            /* $$ = crb_create_binary_expression(GE_EXPRESSION, $1, $3); */
        }
        | relational_expression LT additive_expression
        {
            /* $$ = crb_create_binary_expression(LT_EXPRESSION, $1, $3); */
        }
        | relational_expression LE additive_expression
        {
            /* $$ = crb_create_binary_expression(LE_EXPRESSION, $1, $3); */
        }
        ;
additive_expression
        : multiplicative_expression
        | additive_expression ADD multiplicative_expression
        {
            /* 加减表达式 */
            /* $$ = crb_create_binary_expression(ADD_EXPRESSION, $1, $3); */
        }
        | additive_expression SUB multiplicative_expression
        {
            /* $$ = crb_create_binary_expression(SUB_EXPRESSION, $1, $3); */
        }
        ;
multiplicative_expression
        : unary_expression
        | multiplicative_expression MUL unary_expression
        {
            /* 乘除模表达式 */
            /* $$ = crb_create_binary_expression(MUL_EXPRESSION, $1, $3); */
        }
        | multiplicative_expression DIV unary_expression
        {
            /* $$ = crb_create_binary_expression(DIV_EXPRESSION, $1, $3); */
        }
        | multiplicative_expression MOD unary_expression
        {
            /* $$ = crb_create_binary_expression(MOD_EXPRESSION, $1, $3); */
        }
        ;
unary_expression
        : primary_expression
        | SUB unary_expression
        {
            /* -(a=1) 一元表达式*/
            /* $$ = crb_create_minus_expression($2); */
        }
        ;
primary_expression
        : IDENTIFIER LP argument_list RP
        {
            /* print(a,b) 基本表达式 */
            /* $$ = crb_create_function_call_expression($1, $3); */
        }
        | IDENTIFIER LP RP
        {
            /* print() */
            /* $$ = crb_create_function_call_expression($1, NULL); */
        }
        | LP expression RP
        {
            /* (a=1) */
            /* $$ = $2; */
        }
        | IDENTIFIER
        {
            /* a */
            /* $$ = crb_create_identifier_expression($1); */
        }
        | INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | TRUE_T
        {
            /* $$ = crb_create_boolean_expression(CRB_TRUE); */
        }
        | FALSE_T
        {
            /* $$ = crb_create_boolean_expression(CRB_FALSE); */
        }
        | NULL_T
        {

            /* $$ = crb_create_null_expression(); */
        }
        ;
statement
        : expression SEMICOLON
        {
            /* a = 1; */
            /* $$ = crb_create_expression_statement($1); */
        }
        | global_statement
        | if_statement
        | while_statement
        | for_statement
        | return_statement
        | break_statement
        | continue_statement
        ;
global_statement
        : GLOBAL_T identifier_list SEMICOLON
        {
            /* global a,b; */
            /* $$ = crb_create_global_statement($2); */
        }
        ;
identifier_list
        : IDENTIFIER
        {
            /* a */
            /* $$ = crb_create_global_identifier($1); */
        }
        | identifier_list COMMA IDENTIFIER
        {
            /* a,b */
            /* $$ = crb_chain_identifier($1, $3); */
        }
        ;
if_statement
        : IF LP expression RP block
        {
            /* if (a>1) {} */
            /*$$ = crb_create_if_statement($3, $5, NULL, NULL);*/
        }
        | IF LP expression RP block ELSE block
        {
            /* if (a>1) {} else {} */
            /* $$ = crb_create_if_statement($3, $5, NULL, $7); */
        }
        | IF LP expression RP block elseif_list
        {
            /* if (a>1) {} elseif(){} elseif(){} */
            /* $$ = crb_create_if_statement($3, $5, $6, NULL); */
        }
        | IF LP expression RP block elseif_list ELSE block
        {
            /* if (a>1) {} elseif(){} elseif(){}else{} */
            /* $$ = crb_create_if_statement($3, $5, $6, $8); */
        }
        ;
elseif_list
        : elseif
        | elseif_list elseif
        {
            /* elseif(a>1){}elseif{}... */
        }
        ;
elseif
        : ELSEIF LP expression RP block
        {
            /* elseif(a>1){} */
        }
        ;
while_statement
        : WHILE LP expression RP block
        {
            /* while (a>1) */
        }
        ;
for_statement
        : FOR LP expression_opt SEMICOLON expression_opt SEMICOLON
          expression_opt RP block
        {
            /* for (a=1; a<1; a++) {}*/
        }
        ;
expression_opt
        : /* empty */
        {
            $$ = NULL;
        }
        | expression
        ;
return_statement
        : RETURN_T expression_opt SEMICOLON
        {
            /* return a+1; */
        }
        ;
break_statement
        : BREAK SEMICOLON
        {
            /* break; */
        }
        ;
continue_statement
        : CONTINUE SEMICOLON
        {
            /* continue; */
        }
        ;
block
        : LC statement_list RC
        {
            /* {a = 1; b = 2;} */
        }
        | LC RC
        {
            /* 空块 */
        }
        ;
%%
int yyerror(char const *str)
{
	extern char *yytext;
	fprintf(stderr, "parse error near [%s]\n", yytext);
	return 0;
}