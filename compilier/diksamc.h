typedef struct TypeDerive_tag {
	DeriveTag 	tag;
	union {
		FunctionDerive 	function_d;
	} u;
	struct TypeDerive_tag *next;
}

typedef struct TypeSpecifier_tag TypeSpecifier;

struct TypeSpecifier_tag {
	DVM_BasicType	base_type;
	TypeDerive 		*derive;
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
}

typedef struct {
	char 			*name;
	TypeSpecifier 	*type;
	Expression		*initializer;
	int 				variable_index;
	DVM_Boolean 		is_local;
} Declaration;

typedef struct DeclarationList_tag {
	Declaration 					*declaration;
	struct DeclarationList_tag 	*next;
}

typedef struct Block_tag {
	Block_Type		type;
	struct Block_tag *out_block;
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
}

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
	MEM_Srorage			compile_storage;
	FunctionDefinition	*function_list;
	int					function_count;
	DeclarationList		*declaration_list;
	StatementList		*statement_list;
	int					*current_line_number;
	Block				*current_block;
	DKC_InputMode		input_mode;
	Encoding			source_encoding;
};