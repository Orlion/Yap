#ifndef PRIVATE_DIKSAM_H_INCLUDE
#define PRIVATE_DIKSAM_H_INCLUDE
#include "DKC.h"
#include "MEM.h"

typedef struct TypeSpecifier_tag TypeSpecifier;

typedef struct ParameterList_tag {
	char			*name;
	TypeSpecifier 	*type;
	int 				line_number;
	struct ParameterList_tag 	*next;
} ParameterList;

typedef enum {
	FUNCTION_DERIVE
} DeriveTag;			/* 枚举类型DeriveTag是一种派生类型的表现，现在Diksam中没有数组之类的类型，目前存在的派生类型只有函数类型（FUNCTION_DERIVE）。
								函数（派生类型）的定义保存在FunctionDerive中，具体来说就是参数的类型信息 */

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
}

typedef struct Expression_tag Expression;

struct Expression_tag {
	TypeSpecifier *type;
	ExpressionKind kind;
	int line_number;
	union {
		DVM_Boolean			boolean_value;
		int 					int_value;
		double				double_value;
	}
};

typedef struct {
	char 				*name;
	TypeSpecifier 	*type;
	Expression		*initializer;		/* 构造函数 */
	int 				variable_index;
	DVM_Boolean 	is_local;
} Declaration;		/* 再处理int a；这样的声明语句时，在create.c的阶段会创建Declaration结构体 */

typedef struct DeclarationList_tag {
	Declaration 					*declaration;
	struct DeclarationList_tag 	*next;
}

typedef enum {
	UNDEFINED_BLOCK = 1;
	FUNCTION_BLOCK;
	WHILE_STATEMENT_BLOCK;
	FOR_STATEMENT_BLOCK;
} BlockType;

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

typedef FunctionDefinition_tag FunctionDefinition;

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

struct Statement_tag {
	StatementType 	type;
	int 				line_number;
	union {
		Expression 	*expression_s;
		IfStatement if_s;
		WhileStatement 	while_s;
		ForStatement 	for_s;
		ForeachStatement 	foreach_s;
		BreakStatement 		break_s;
		ContinueStatement 	continue_s;
		ReturnStatement 		return_s;
		TryStatement 		try_s;
		ThrowStatement 		throw_s;
		Declaration 			*declaration_s;
	} u;
};

typedef StatementList_tag {
	Statement  *statement;
	struct StatementList_tag *next;
} StatementList;

typedef enum {
	ENU_ENCODING = 1,
	SHIFT_JIS_ENCODING,
	UTF_8_ENCODING
} Encoding;

struct DKC_Compiler_tag {
	MEM_Srorage				compile_storage;
	FunctionDefinition		*function_list;
	int						function_count;
	DeclarationList			*declaration_list;
	StatementList			*statement_list;
	int						*current_line_number;
	Block					*current_block;			/* 当前程序块，当程序块开始时（匹配到{时）设置current_block */
	DKC_InputMode			input_mode;
	Encoding				source_encoding;
};

void dkc_set_current_compiler(DKC_Compiler *compiler);