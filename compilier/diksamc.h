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