%{
#include <stdio.h>
#include <stdlib.h>	
#include "yaplang.h"
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
            YAP_Interpreter *inter = yap_get_current_interpreter();

            inter->statement_list = yap_chain_statement_list(inter->statement_list, $1);
        }
        ;
function_definition
        : FUNCTION IDENTIFIER LP parameter_list RP block
        {
            /* 函数定义 function abc(def, ghi) {} */
            yap_function_define($2, $4, $6);
        }
        | FUNCTION IDENTIFIER LP RP block
        {
            yap_function_define($2, NULL, $5);
        }
        ;
parameter_list
        : IDENTIFIER
        {
            /* 形参 */
            $$ = yap_create_parameter($1);
        }
        | parameter_list COMMA IDENTIFIER
        {
            $$ = yap_chain_parameter($1, $3);
        }
        ;
argument_list
        : expression
        {
            /* 实参 */
            $$ = yap_create_argument_list($1);
        }
        | argument_list COMMA expression
        {
            $$ = yap_chain_argument_list($1, $3);
        }
        ;
statement_list
        : statement
        {
            $$ = yap_create_statement_list($1);
        }
        | statement_list statement
        {
            $$ = yap_chain_statement_list($1, $2);
        }
        ;
expression
        : logical_or_expression
        | IDENTIFIER ASSIGN expression
        {
            $$ = yap_create_assign_expression($1, $3);
        }
        ;
logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGICAL_OR logical_and_expression
        {
            $$ = yap_create_binary_expression(LOGICAL_OR_EXPRESSION, $1, $3);
        }
        ;
logical_and_expression
        : equality_expression
        | logical_and_expression LOGICAL_AND equality_expression
        {
            $$ = yap_create_binary_expression(LOGICAL_AND_EXPRESSION, $1, $3);
        }
        ;
equality_expression
        : relational_expression
        | equality_expression EQ relational_expression
        {
            $$ = yap_create_binary_expression(EQ_EXPRESSION, $1, $3);
        }
        | equality_expression NE relational_expression
        {
            $$ = yap_create_binary_expression(NE_EXPRESSION, $1, $3);
        }
        ;
relational_expression
        : additive_expression
        | relational_expression GT additive_expression
        {
            $$ = yap_create_binary_expression(GT_EXPRESSION, $1, $3);
        }
        | relational_expression GE additive_expression
        {
            $$ = yap_create_binary_expression(GE_EXPRESSION, $1, $3);
        }
        | relational_expression LT additive_expression
        {
            $$ = yap_create_binary_expression(LT_EXPRESSION, $1, $3);
        }
        | relational_expression LE additive_expression
        {
            $$ = yap_create_binary_expression(LE_EXPRESSION, $1, $3);
        }
        ;
additive_expression
        : multiplicative_expression
        | additive_expression ADD multiplicative_expression
        {
            /* 加减表达式 */
            $$ = yap_create_binary_expression(ADD_EXPRESSION, $1, $3);
        }
        | additive_expression SUB multiplicative_expression
        {
            $$ = yap_create_binary_expression(SUB_EXPRESSION, $1, $3);
        }
        ;
multiplicative_expression
        : unary_expression
        | multiplicative_expression MUL unary_expression
        {
            /* 乘除模表达式 */
            $$ = yap_create_binary_expression(MUL_EXPRESSION, $1, $3);
        }
        | multiplicative_expression DIV unary_expression
        {
            $$ = yap_create_binary_expression(DIV_EXPRESSION, $1, $3);
        }
        | multiplicative_expression MOD unary_expression
        {
            $$ = yap_create_binary_expression(MOD_EXPRESSION, $1, $3);
        }
        ;
unary_expression
        : primary_expression
        | SUB unary_expression
        {
            $$ = yap_create_minus_expression($2);
        }
        ;
primary_expression
        : IDENTIFIER LP argument_list RP
        {
            $$ = yap_create_function_call_expression($1, $3);
        }
        | IDENTIFIER LP RP
        {
            $$ = yap_create_function_call_expression($1, NULL);
        }
        | LP expression RP
        {
            $$ = $2;
        }
        | IDENTIFIER
        {
            $$ = yap_create_identifier_expression($1);
        }
        | INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | TRUE_T
        {
            $$ = yap_create_boolean_expression(YAP_TRUE);
        }
        | FALSE_T
        {
            $$ = yap_create_boolean_expression(YAP_FALSE);
        }
        | NULL_T
        {

            $$ = yap_create_null_expression();
        }
        ;
statement
        : expression SEMICOLON
        {
            $$ = yap_create_expression_statement($1);
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
            $$ = yap_create_global_statement($2);
        }
        ;
identifier_list
        : IDENTIFIER
        {
            $$ = yap_create_global_identifier($1);
        }
        | identifier_list COMMA IDENTIFIER
        {
            $$ = yap_chain_identifier($1, $3);
        }
        ;
if_statement
        : IF LP expression RP block
        {
            $$ = yap_create_if_statement($3, $5, NULL, NULL);
        }
        | IF LP expression RP block ELSE block
        {
            $$ = yap_create_if_statement($3, $5, NULL, $7);
        }
        | IF LP expression RP block elseif_list
        {
            $$ = yap_create_if_statement($3, $5, $6, NULL);
        }
        | IF LP expression RP block elseif_list ELSE block
        {
            $$ = yap_create_if_statement($3, $5, $6, $8);
        }
        ;
elseif_list
        : elseif
        | elseif_list elseif
        {
            $$ = yap_chain_elseif_list($1, $2);
        }
        ;
elseif
        : ELSEIF LP expression RP block
        {
            $$ = yap_create_elseif($3, $5);
        }
        ;
while_statement
        : WHILE LP expression RP block
        {
            $$ = yap_create_while_statement($3, $5);
        }
        ;
for_statement
        : FOR LP expression_opt SEMICOLON expression_opt SEMICOLON
          expression_opt RP block
        {
            $$ = yap_create_for_statement($3, $5, $7, $9);
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
            $$ = yap_create_return_statement($2);
        }
        ;
break_statement
        : BREAK SEMICOLON
        {
            $$ = yap_create_break_statement();
        }
        ;
continue_statement
        : CONTINUE SEMICOLON
        {
            $$ = yap_create_continue_statement();
        }
        ;
block
        : LC statement_list RC
        {
            $$ = yap_create_block($2);
        }
        | LC RC
        {
            $$ = yap_create_block(NULL);
        }
        ;
%%
int yyerror(char const *str)
{
	extern char *yytext;
	fprintf(stderr, "parse error near [%s]\n", yytext);
	return 0;
}