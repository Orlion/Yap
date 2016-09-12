%{
#include "diksamc.h"
#define YYDEBUG 1	
%}
%union {
	char 				*identifier;
	ParameterList 		*parameter_list;
	ArgumentList 		*argument_list;
	Expression 			*expression;
	Statement 			*statement;
	StatementList		*statement_list;
	Block 				*block;
	Elseif 				*elseif;
	AssignmentOperator 	assignment_operator;
	DVM_BasicType 		type_specifier;
}
%token <expression>	INT_LITERAL
%token <expression>	DOUBLE_LITERAL
%token <expression>	STRING_LITERAL
%token <expression>	REGEXP_LITERAL
%token <identifier>	IDENTIFIER
%token IF ELSE ELSEIF WHILE FOR FOREACH RETURN_T BREAK CONTINUE
		LP RP LC RC SEMICOLON COLON COMMA ASSIGN_T LOGICAL_AND
		LOGICAL_OR
		EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T EXCLAMATION DOT
        	ADD_ASSIGN_T SUB_ASSIGN_T MUL_ASSIGN_T DIV_ASSIGN_T MOD_ASSIGN_T
        	INCREMENT DECREMENT TRY CATCH FINALLY THROW
        	BOOLEAN_T INT_T DOUBLE_T STRING_T
%type <prarameter_list> parameter_list
%type <argument_list> argument_list
%type <expression> expression expression_opt
		assignment_expression logical_and_expression logical_or_expression equality_expression relational_expression
		additive_expression multiplicative_expression
		unary_expression postfix_expression primary_expression
%type <statement> statement
		if_statement while_statement for_statement foreach_statement
		return_statement break_statement continue_statement
		try_statement throw_statement declaration_statement
%type <statement_list> statement_list
%type <block> block
%type <elseif> elseif elseif_list
%type <assignment_operator> assignment_operator
%type <identifier> identifier_opt label_opt
%type <type_specifier> type_specifier
%%
translation_unit
	: definition_or_statement
	| translation_unit definition_or_statement
	;
definition_or_statement
	: function_definition
	| statement
	{

	}
	;
type_specifier
	: BOOLEAN_T
	{

	}
	| INT_T
	{

	}
	| DOUBLE_T
	{

	}
	| STRING_T
	{

	}
	;
function_definition
	: type_specifier IDENTIFIER LP parameter_list RP block
	{

	}
	| type_specifier IDENTIFIER LP RP block
	{

	}
	| type_specifier IDENTIFIER LP parameter_list RP SEMICOLON
	{

	}
	| type_specifier IDENTIFIER LP RP SEMICOLON
	{

	}
	;
parameter_list
	: type_specifier IDENTIFIER
	{

	}
	| parameter_list COMMA type_specifier IDENTIFIER
	{

	}
	;
argument_list
	: assignment_expression
	{

	}
	| argument_list COMMA assignment_expression
	{

	}
	;
statement_list
	: statement
	{

	}
	| statement_list statement
	{

	}
	;
expression
	: assignment_expression
	| expression COMMA assignment_expression
	{

	}
	;
assignment_expression
	: logical_or_expression
	| postfix_expression assignment_operator assignment_expression
	{

	}
	;
assignment_operator
	: ASSIGN_T
	{

	}
	| ADD_ASSIGN_T
	{

	}
	| SUB_ASSIGN_T
	{

	}
	| MUL_ASSIGN_T
	{

	}
	| DIV_ASSIGN_T
	{

	}
	| MOD_ASSIGN_T
	{

	}
	;
logical_or_expression
	: logical_and_expression
	| logical_or_expression LOGICAL_OR logical_and_expression
	{

	}
	;
logical_and_expression
	: equality_expression
	| logical_and_expression LOGICAL_AND equality_expression
	{

	}
	;
equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	{

	}
	| equality_expression NE relational_expression
	{

	}
	;
relational_expression
	: additive_expression
	| relational_expression GT additive_expression
	{

	}
	| relational_expression GE additive_expression
	{

	}
	| relational_expression LT additive_expression
	{

	}
	| relational_expression LE additive_expression
	{

	}
	;
additive_expression
	: multiplicative_expression
	| additive_expression ADD multiplicative_expression
	{

	}
	| additive_expression SUB multiplicative_expression
	{

	}
	;
multiplicative_expression
	: unary_expression
	| multiplicative_expression MUL unary_expression
	{

	}
	| multiplicative_expression DIV unary_expression
	{

	}
	| multiplicative_expression MOD unary_expression
	{

	}
	;
unary_expression
	: postfix_expression
	| SUB unary_expression
	{

	}
	| EXCLAMATION unary_expression
	{

	}
	;
postfix_expression
	: primary_expression
	| postfix_expression LP argument_list RP
	{

	}
	| postfix_expression LP RP
	{

	}
	| postfix_expression INCREMENT
	{

	}
	| postfix_expression DECREMENT
	{

	}
	;
primary_expression
	: LP expression RP
	{

	}
	| IDENTIFIER
	{

	}
	| INT_LITERAL
	| DOUBLE_LITERAL
	| STRING_LITERAL
	| REGEXP_LITERAL
	| TRUE_T
	{

	}
	| FALSE_T
	{

	}
	;
statement
	: expression SEMICOLON
	{

	}
	| if_statement
	| while_statement
	| for_statement
	| foreach_statement
	| return_statement
	| break_statement
	| continue_statement
	| try_statement
	| throw_statement
	| declaration_statement
	;
if_statement
	: IF LP expression RP block
	{

	}
	| IF LP expression RP block ELSE block
	{

	}
	| IF LP expression RP block elseif_list
	{

	}
	| IF LP expression RP block elseif_list ELSE block
	{

	}
	;
elseif_list
	: elseif
	| elseif_list elseif
	{

	}
	;
elseif
	: ELSEIF LP expression RP block
	{

	}
	;
label_opt
	: /* empty */
	{
		$$ = NULL;
	}
	| IDENTIFIER COLON
	{

	}
	;
while_statement
	: label_opt WHILE LP expression RP block
	{

	}
	;
for_statement
	: label_opt FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP block
	{

	}
	;
foreach_statement
	: label_opt FOREACH LP IDENTIFIER COLON expression RP block
	{

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

	}
	;
identifier_opt
	: /* empty */
	{
		$$ = NULL;
	}
	| IDENTIFIER
	;
break_statement
	: BREAK identifier_opt SEMICOLON
	{

	}
	;
continue_statement
	: CONTINUE identifier_opt SEMICOLON
	{

	}
	;
try_statement
	: TRY block CATCH LP IDENTIFIER RP block FINALLY block
	{

	}
	| TRY block FINALLY block
	{

	}
	| TRY block CATCH LP IDENTIFIER RP block
	{

	}
throw_statement
	: THROW expression SEMICOLON
	{

	}
declaration_statement
	: type_specifier IDENTIFIER SEMICOLON
	{

	}
	| type_specifier IDENTIFIER ASSIGN_T expression SEMICOLON
	{

	}
	;
block
	: LC
	{

	}
	 statement_list RC
	{

	}
	| LC RC
	{

	}
	;
%%