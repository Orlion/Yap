#ifndef PRIVATE_DIKSAMC_H_INCLUDED
#define PRIVATE_DIKSAMC_H_INCLUDED
#include <stdio.h>
#include "MEM.h"
#include "DKC.h"
#include "DVM_code.h"

#define smaller(a, b) ((a) < (b) ? (a) : (b))
#define larger(a, b) ((a) > (b) ? (a) : (b))

#define LINE_BUF_SIZE           (1024)

typedef struct TypeSpecifier_tag TypeSpecifier;

typedef enum {
	FUNCTION_DERIVE
} DeriveTag;			/* 枚举类型DeriveTag是一种派生类型的表现，现在Diksam中没有数组之类的类型，目前存在的派生类型只有函数类型
					（FUNCTION_DERIVE）。函数（派生类型）的定义保存在FunctionDerive中，具体来说就是参数的类型信息 */

typedef struct ParameterList_tag {
	char			*name;
	TypeSpecifier 	*type;
	int 				line_number;
	struct ParameterList_tag 	*next;
} ParameterList;

typedef struct {
	ParameterList *paramter_list;
} FunctionDerive;		/* 函数（派生类型）的定义保存在FunctionDerive中，具体来说就是参数的类型信息 */

typedef struct TypeDerive_tag {
	DeriveTag 	tag;
	union {
		FunctionDerive 	function_d;
	} u;
	struct TypeDerive_tag *next;
} TypeDerive;

struct TypeSpecifier_tag {
	DVM_BasicType	base_type;		/* 基本数据类型 */
	TypeDerive 		*derive;			/* 派生类型 */
};

typedef struct Expression_tag Expression;

typedef struct ArgumentList_tag {
	Expression 	*expression;
	struct 		ArgumentList_tag 	*next;
} ArgumentList;

typedef struct {
	char 				*name;
	TypeSpecifier 	*type;
	Expression		*initializer;		/* 构造函数 */
	int 				variable_index;
	DVM_Boolean 	is_local;
} Declaration;		/* 再处理int a；这样的声明语句时，在create.c的阶段会创建Declaration结构体 */

typedef enum {
	BOOLEAN_EXPRESSION = 1,
	INT_EXPRESSION,
	DOUBLE_EXPRESSION,
	STRING_EXPRESSION,
	IDENTIFIER_EXPRESSION,
	COMMA_EXPRESSION,
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
	LOGICAL_NOT_EXPRESSION,
	FUNCTION_CALL_EXPRESSION,
	INCREMENT_EXPRESSION,
	DECREMENT_EXPRESSION,
	CAST_EXPRESSION,
	EXPRESSION_KIND_COUNT_PLUS_1
} ExpressionKind;

typedef struct FunctionDefinition_tag FunctionDefinition;

typedef struct {
	char 	*name;
	DVM_Boolean 	is_function;
	union {
		FunctionDefinition  *function;
		Declaration 			*declaration;
	} u;
} IdentifierExpression;

typedef struct {
	Expression *left;
	Expression *right;
} CommaExpression;

typedef enum {
	NORMAL_ASSIGN = 1,
	ADD_ASSIGN,
	SUB_ASSIGN,
	MUL_ASSIGN,
	DIV_ASSIGN,
	MOD_ASSIGN
} AssignmentOperator;

typedef struct {
	AssignmentOperator operator;
	Expression *left;
	Expression *right;
} AssignExpression;

typedef struct {
	Expression *left;
	Expression *right;
} BinaryExpression;

typedef struct {
	Expression 		*function;
	ArgumentList 	*argument;
} FunctionCallExpression;

typedef struct {
	Expression *operand;
} IncrementOrDecrement;

typedef enum {
	INT_TO_DOUBLE_CAST,
	DOUBLE_TO_INT_CAST,
	BOOLEAN_TO_STRIING_CAST,
	INT_TO_STRING_CAST,
	DOUBLE_TO_STRING_CAST
} CastType;

typedef struct {
	CastType 	type;
	Expression 	*operand;
} CastExpression;

struct Expression_tag {
	TypeSpecifier *type;
	ExpressionKind kind;
	int line_number;
	union {
		DVM_Boolean				boolean_value;
		int 						int_value;
		double					double_value;
		DVM_Char 				*string_value;
		IdentifierExpression 	identifier;
		CommaExpression 			comma;
		AssignExpression 		assign_expression;
		BinaryExpression 		binary_expression;
		Expression 				*minus_expression;
		Expression 				*logical_not;
		FunctionCallExpression 	function_call_expression;
		IncrementOrDecrement 	inc_dec;
		CastExpression 			cast;
	} u;
};

typedef struct DeclarationList_tag {
	Declaration 					*declaration;
	struct DeclarationList_tag 	*next;
} DeclarationList;

typedef struct Statement_tag Statement;

typedef struct StatementList_tag {
	Statement  *statement;
	struct StatementList_tag *next;
} StatementList;

typedef enum {
	UNDEFINED_BLOCK = 1,
	FUNCTION_BLOCK,
	WHILE_STATEMENT_BLOCK,
	FOR_STATEMENT_BLOCK
} BlockType;

typedef struct {
	Statement 	*statement;
	int 			continue_label;
	int 			break_label;
} StatementBlockInfo;

typedef struct {
	FunctionDefinition 	*function;
	int 					end_label;
} FunctionBlockInfo;

typedef struct Block_tag {
	BlockType		type;
	struct Block_tag *out_block;		/* 上层程序块，查找变量时先从当前代码块查找再从上层代码块查找 */
	StatementList 	*statement_list;
	DeclarationList  *declaration_list;
	union {
		StatementBlockInfo 	statement;
		FunctionBlockInfo	function;
	} parent;
} Block;

struct FunctionDefinition_tag {
	TypeSpecifier		*type;
	char				*name;
	ParameterList		*parameter;
	Block 				*block;
	int 					local_variable_count;
	Declaration   		**local_variable;
	int 					index;
	struct FunctionDefinition_tag	*next;
};

typedef enum {
	EXRPESSION_STATEMENT = 1,
	IF_STATEMENT,
	WHILE_STATEMNET,
	FOR_STATEMENT,
	FOREACH_STATEMENT,
	RETURN_STATEMENT,
	BREAK_STATEMENT,
	CONTINUE_STATEMENT,
	TRY_STATEMENT,
	THROW_STATEMENT,
	DECLARATION_STATEMENT,
	STATEMENT_TYPE_COUNT_PLUS_1
} StatementType;

typedef struct Elseif_tag {
	Expression 	*condition;
	Block 		*block;
	struct Elseif_tag *next;
} Elseif;

typedef struct {
	Expression *condition;
	Block 		*then_block;
	Elseif 		*elseif_block;
	Block 		*else_block;
} IfStatement;

typedef struct {
	char 		*label;
	Expression 	*condition;
	Block 		*block;
} WhileStatement;

typedef struct {
	char 	*label;
	Expression 	*init;
	Expression 	*condition;
	Expression 	*post;
	Expression 	*block;
} ForStatement;

typedef struct {
	char 		*label;
	char 		*variable;
	Expression 	*collection;
	Block 		*block;
} ForeachStatement;

typedef struct {
	Expression 	*return_value;
} ReturnStatement;

typedef struct {
	char 	*label;
} BreakStatement;

typedef struct {
	char 	*label;
} ContinueStatement;

typedef struct {
	Block 	*try_block;
	Block 	*catch_block;
	char 	*exception;
	Block 	*finally_block;
} TryStatement;

typedef struct {
	Expression *expression;
} ThrowStatement;

struct Statement_tag {
	StatementType 	type;
	int 				line_number;
	union {
		Expression 			*expression_s;
		IfStatement 			if_s;
		WhileStatement 		while_s;
		ForStatement 		for_s;
		ForeachStatement 	foreach_s;
		BreakStatement 		break_s;
		ContinueStatement 	continue_s;
		ReturnStatement 		return_s;
		TryStatement 		try_s;
		ThrowStatement 		throw_s;
		Declaration 			*declaration_s;
	} u;
};

typedef enum {
	ENU_ENCODING = 1,
	SHIFT_JIS_ENCODING,
	UTF_8_ENCODING
} Encoding;

struct DKC_Compiler_tag {
	FunctionDefinition		*function_list;
	int						function_count;
	DeclarationList			*declaration_list;
	StatementList			*statement_list;
	int						current_line_number;
	Block					*current_block;			/* 当前程序块，当程序块开始时（匹配到{时）设置current_block */
	DKC_InputMode			input_mode;
	Encoding				source_encoding;
	MEM_Storage				compile_storage;
};

/* util.c */
DKC_Compiler *dkc_get_current_compiler(void);
void dkc_set_current_compiler(DKC_Compiler *compiler);
void *dkc_malloc(size_t size);
TypeSpecifier *dkc_alloc_type_specifier(DVM_BasicType type);
FunctionDefinition *dkc_search_function(char *name);
Declaration *dkc_search_declaration(char *identifier, Block *block);

/* interface.c */
void dkc_compile_error(int line_number, char *msg);

/* string.c */
char *dkc_create_identifier(char *str);
void dkc_open_string_literal(void);
void dkc_add_string_literal(int letter);
DVM_Char *dkc_close_string_literal(void);

/* create.c */
Statement *dkc_create_for_statement(char *label, Expression *init, Expression *cond, Expression *post, Block *block);

Statement *dkc_create_foreach_statement(char *label, char *variable, Expression *collection, Block *block);

Statement *dkc_create_return_statement(Expression *expression);

Statement *dkc_create_break_statement(char *label);

Statement *dkc_create_continue_statement(char *label);

Statement *dkc_create_try_statement(Block *try_block, char *exception, Block *catch_block, Block *finally_block);

Statement *dkc_create_throw_statement(Expression *expression);

Expression *dkc_alloc_expression(ExpressionKind kind);

Statement *dkc_create_declaration_statement(DVM_BasicType type, char *identifier, Expression *initializer);

Block *dkc_open_block(void);
Block *dkc_close_block(Block *block, StatementList *statement_list);

Statement *dkc_create_while_statement(char *label, Expression *condition, Block *block);

Elseif *dkc_create_elseif(Expression *expr, Block *block);

Elseif *dkc_chain_elseif_list(Elseif *list, Elseif *add);

Statement *dkc_create_if_statement(Expression *condition, Block *then_block, Elseif *elseif_list, Block *else_block);

Statement *dkc_create_expression_statement(Expression *expression);

Expression *dkc_create_boolean_expression(DVM_Boolean value);

Expression *dkc_create_identifier_expression(char *identifier);

Expression *dkc_create_incdec_expression(Expression *operand, ExpressionKind inc_or_dec);

Expression *dkc_create_function_call_expression(Expression *function, ArgumentList *argument);

Expression *dkc_create_logical_not_expression(Expression *operand);

Expression *dkc_create_minus_expression(Expression *operand);

Expression *dkc_create_binary_expression(ExpressionKind operator, Expression *left, Expression *right);

Expression *dkc_create_assign_expression(Expression *left, AssignmentOperator operator, Expression *operand);

Expression *dkc_create_comma_expression(Expression *left, Expression *right);

StatementList *dkc_chain_statement_list(StatementList *list, Statement *statement);

StatementList *dkc_create_statement_list(Statement *statement);

ArgumentList *dkc_create_argument_list(Expression *expression);

ArgumentList *dkc_chain_argument_list(ArgumentList *list, Expression *expr);

ParameterList *dkc_create_parameter(DVM_BasicType type, char *identifier);

ParameterList *dkc_chain_parameter(ParameterList *list, DVM_BasicType type, char *identifier);

void dkc_function_define(DVM_BasicType type, char *identifier, ParameterList *paramter_list, Block *block);

StatementList *dkc_chain_statement_list(StatementList *list, Statement *statement);

#endif