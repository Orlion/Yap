#ifndef PRIVATE_YAP_H_INCLUDED
#define PRIVATE_YAP_H_INCLUDED
#include "YAP_dev.h"

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
    struct Elsif_tag    *next;
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
	YAP_FUNCTION_DEFINTION = 1,		/* 用户在yap中自定义函数 */
	NATIVE_FINCTION_DEFINITION		/* yap的内置函数 */
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
		} natice_f;
	} u;
	struct FunctionDefinition_tag 	*next;
} FunctionDefinition;

/* 变量 */
typedef struct Variable_tag {
	char					*name;
	YAP_Value 				value;
	struct Variable_tag 	*next;
} Variable;

/* 解释器 */
struct CRB_Interpreter_tag {
    MEM_Storage         interpreter_storage;
    MEM_Storage         execute_storage;
    Variable            *variable;
    FunctionDefinition  *function_list;
    StatementList       *statement_list;
    int                 current_line_number;
};

#endif /* PRIVATE_YAP_H_INCLUDED */