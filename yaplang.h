#ifndef PRIVATE_YAP_H_INCLUDED
#define PRIVATE_YAP_H_INCLUDED
#include <stdio.h>
#include "MEM.h"
#include "YAP.h"
#include "YAP_dev.h"

typedef enum {
    PARSE_ERR = 1,
    CHARACTER_INVALID_ERR,
    FUNCTION_MULTIPLE_DEFINE_ERR,
    COMPILE_ERROR_COUNT_PLUS_1
} CompileError;

typedef enum {
    VARIABLE_NOT_FOUND_ERR = 1,
    FUNCTION_NOT_FOUND_ERR,
    ARGUMENT_TOO_MANY_ERR,
    ARGUMENT_TOO_FEW_ERR,
    NOT_BOOLEAN_TYPE_ERR,
    MINUS_OPERAND_TYPE_ERR,
    BAD_OPERAND_TYPE_ERR,
    NOT_BOOLEAN_OPERATOR_ERR,
    FOPEN_ARGUMENT_TYPE_ERR,
    FCLOSE_ARGUMENT_TYPE_ERR,
    FGETS_ARGUMENT_TYPE_ERR,
    FPUTS_ARGUMENT_TYPE_ERR,
    NOT_NULL_OPERATOR_ERR,
    DIVISION_BY_ZERO_ERR,
    GLOBAL_VARIABLE_NOT_FOUND_ERR,
    GLOBAL_STATEMENT_IN_TOPLEVEL_ERR,
    BAD_OPERATOR_FOR_STRING_ERR,
    RUNTIME_ERROR_COUNT_PLUS_1
} RuntimeError;

typedef enum {
    INT_MESSAGE_ARGUMENT = 1,
    DOUBLE_MESSAGE_ARGUMENT,
    STRING_MESSAGE_ARGUMENT,
    CHARACTER_MESSAGE_ARGUMENT,
    POINTER_MESSAGE_ARGUMENT,
    MESSAGE_ARGUMENT_END
} MessageArgumentType;

/* 表达式类型 */
typedef enum {
    BOOLEAN_EXPRESSION = 1,
    INT_EXPRESSION,
    DOUBLE_EXPRESSION,
    STRING_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    ASSIGN_EXPRESSION,
    ADD_EXPRESSION,
    SUB_EXPRESSION,
    MUL_EXPRESSION,
    DIV_EXPRESSION,
    MOD_EXPRESSION,
    EQ_EXPRESSION,
    NE_EXPRESSION,
    GT_EXPRESSION,
    GE_EXPRESSION,
    LT_EXPRESSION,
    LE_EXPRESSION,
    LOGICAL_AND_EXPRESSION,
    LOGICAL_OR_EXPRESSION,
    MINUS_EXPRESSION,
    FUNCTION_CALL_EXPRESSION,
    NULL_EXPRESSION,
    EXPRESSION_TYPE_COUNT_PLUS_1
} ExpressionType;

typedef struct Expression_tag Expression;

/* 赋值表达式 */
typedef struct {
    char        *variable;
    Expression  *operand;
} AssignExpression;

/* 二元表达式 */
typedef struct {
    Expression  *left;
    Expression  *right;
} BinaryExpression;

/* 实参列表 */
typedef struct ArgumentList_tag {
	Expression	*expression;
	struct 		ArgumentList_tag *next;
} ArgumentList;

/* 调用函数表达式 */
typedef struct {
    char                *identifier;
    ArgumentList        *argument;
} FunctionCallExpression;

/* 表达式 */
struct Expression_tag {
	ExpressionType type;
	int line_number;
	union {
		YAP_Boolean boolean_value;
		int			int_value;
		double		double_value;
		char		*string_value;
		char		*identifier;
		AssignExpression	assign_expression;
		BinaryExpression	binary_expression;
		Expression 			*minus_expression;
		FunctionCallExpression 		function_call_expression;
	} u;
};

/* 语句 */
typedef struct Statement_tag Statement;

/* 语句列表 */
typedef struct StatementList_tag {
    Statement   *statement;
    struct 		StatementList_tag    *next;
} StatementList;

typedef struct {
    StatementList       *statement_list;
} Block;

/* 标识符列表 */
typedef struct IdentifierList_tag {
    char        *name;
    struct 		IdentifierList_tag   *next;
} IdentifierList;

/* 全局声明语句 */
typedef struct {
    IdentifierList      *identifier_list;
} GlobalStatement;

/* elseif */
typedef struct Elseif_tag {
    Expression  *condition;
    Block       *block;
    struct Elseif_tag    *next;
} Elseif;

/* if语句 */
typedef struct {
    Expression  *condition;
    Block       *then_block;
    Elseif       *elseif_list;
    Block       *else_block;
} IfStatement;

/* while语句 */
typedef struct {
    Expression  *condition;
    Block       *block;
} WhileStatement;

/* for语句 */
typedef struct {
    Expression  *init;
    Expression  *condition;
    Expression  *post;
    Block       *block;
} ForStatement;

/* 返回语句 */
typedef struct {
    Expression *return_value;
} ReturnStatement;

/* 语句类型 */
typedef enum {
    EXPRESSION_STATEMENT = 1,		/* 表达式语句 a = 1; */
    GLOBAL_STATEMENT,				/* 全局声明语句 */
    IF_STATEMENT,					/* if语句 */
    WHILE_STATEMENT,				/* while语句 */
    FOR_STATEMENT,					/* for语句 */
    RETURN_STATEMENT,				/* 返回语句 */
    BREAK_STATEMENT,				/* break语句 */
    CONTINUE_STATEMENT,				/* continue语句 */
    STATEMENT_TYPE_COUNT_PLUS_1		/* 表达式语句 */
} StatementType;

/* 语句 */
struct Statement_tag {
    StatementType       type;
    int                 line_number;
    union {
        Expression      *expression_s;
        GlobalStatement global_s;
        IfStatement     if_s;
        WhileStatement  while_s;
        ForStatement    for_s;
        ReturnStatement return_s;
    } u;
};

/* 形参列表 */
typedef struct ParameterList_tag {
    char        *name;
    struct 		ParameterList_tag *next;
} ParameterList;

/* 函数类型 */
typedef enum {
	YAP_FUNCTION_DEFINITION = 1,		/* 用户在yap中自定义函数 */
	NATIVE_FUNCTION_DEFINITION		/* yap的内置函数 */
} FunctionDefinitionType;

/* 函数 */
typedef struct FunctionDefinition_tag {
	char	*name;							/* 函数名 */
	FunctionDefinitionType 	type;			/* 自定义还是原生函数 */
	union {
		struct {
			ParameterList 	*parameter;
			Block 			*block;
		} yap_f;
		struct {
			YAP_NativeFunctionProc 	*proc;
		} native_f;
	} u;
	struct FunctionDefinition_tag 	*next;
} FunctionDefinition;

/* 变量 */
typedef struct Variable_tag {
	char					*name;
	YAP_Value 				value;
	struct Variable_tag 	*next;
} Variable;

struct YAP_String_tag {
    int         ref_count;
    char        *string;
    YAP_Boolean is_literal;
};

struct YAP_Interpreter_tag {
    MEM_Storage         interpreter_storage;
    MEM_Storage         execute_storage;
    Variable            *variable;
    FunctionDefinition  *function_list;
    StatementList       *statement_list;
    int                 current_line_number;
};

typedef struct GlobalVariableRef_tag {
    Variable    *variable;
    struct GlobalVariableRef_tag *next;
} GlobalVariableRef;

typedef struct {
    Variable    *variable;
    GlobalVariableRef   *global_variable;
} LocalEnvironment;

typedef enum {
    NORMAL_STATEMENT_RESULT = 1,
    RETURN_STATEMENT_RESULT,
    BREAK_STATEMENT_RESULT,
    CONTINUE_STATEMENT_RESULT,
    STATEMENT_RESULT_TYPE_COUNT_PLUS_1
} StatementResultType;

typedef struct {
    StatementResultType type;
    union {
        YAP_Value       return_value;
    } u;
} StatementResult;


/* create.c */
void yap_function_define(char *identifier, ParameterList *parameter_list, Block *block);
ParameterList *yap_create_parameter(char *identifier);
ParameterList *yap_chain_parameter(ParameterList *list, char *identifier);
ArgumentList *yap_create_argument_list(Expression *expression);
ArgumentList *yap_chain_argument_list(ArgumentList *list, Expression *expr);
StatementList *yap_create_statement_list(Statement *statement);
StatementList *yap_chain_statement_list(StatementList *list, Statement *statement);
Expression *yap_alloc_expression(ExpressionType type);
Expression *yap_create_assign_expression(char *variable, Expression *operand);
Expression *yap_create_binary_expression(ExpressionType operator, Expression *left, Expression *right);
Expression *yap_create_minus_expression(Expression *operand);
Expression *yap_create_identifier_expression(char *identifier);
Expression *yap_create_function_call_expression(char *func_name, ArgumentList *argument);
Expression *yap_create_boolean_expression(YAP_Boolean value);
Expression *yap_create_null_expression(void);
Statement *yap_create_global_statement(IdentifierList *identifier_list);
IdentifierList *yap_create_global_identifier(char *identifier);
IdentifierList *yap_chain_identifier(IdentifierList *list, char *identifier);
Statement *yap_create_if_statement(Expression *condition, Block *then_block, Elseif *elseif_list, Block *else_block);
Elseif *yap_chain_elseif_list(Elseif *list, Elseif *add);
Elseif *yap_create_elseif(Expression *expr, Block *block);
Statement *yap_create_while_statement(Expression *condition, Block *block);
Statement *yap_create_for_statement(Expression *init, Expression *cond, Expression *post, Block *block);
Block *yap_create_block(StatementList *statement_list);
Statement *yap_create_expression_statement(Expression *expression);
Statement *yap_create_return_statement(Expression *expression);
Statement *yap_create_break_statement(void);
Statement *yap_create_continue_statement(void);

/* native.c */
YAP_Value yap_nv_print_proc(YAP_Interpreter *interpreter, int arg_count, YAP_Value *args);

/* util.c */
void yap_set_current_interpreter(YAP_Interpreter *inter);
YAP_Interpreter *yap_get_current_interpreter(void);
FunctionDefinition *yap_search_function(char *name);
void *yap_malloc(size_t size);

/* error.c */
void yap_compile_error(char *msg);

void yap_runtime_error(char *msg);

/* string.c */
void yap_open_string_literal(void);
void yap_add_string_literal(int letter);
char *yap_create_identifier(char *str);
char *yap_close_string_literal(void);
void yup_reset_string_literal_buffer(void);

/* execute.c */
StatementResult yap_execute_statement_list(YAP_Interpreter *inter, LocalEnvironment *env, StatementList *list);

#define dkc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)

#define dkc_is_compare_operator(operator) \
  ((operator) == EQ_EXPRESSION || (operator) == NE_EXPRESSION\
   || (operator) == GT_EXPRESSION || (operator) == GE_EXPRESSION\
   || (operator) == LT_EXPRESSION || (operator) == LE_EXPRESSION)
#endif /* PRIVATE_YAP_H_INCLUDED */