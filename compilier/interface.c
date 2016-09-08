DKC_Compilier *DKC_create_compilier(void)
{
	MEM_Storage storage;
	DKC_Compilier *compilier;

	storage = MEM_open_storage(0);
	compilier = MEM_storage_malloc(storage, sizeof(struct DKC_Compilier_tag));
	compilier->compilie_strorage = storage;
	compiler->function_list = NULL;
	compiler->function_count = 0;
	compiler->declaration_list = NULL;
	compiler->statement_list = NULL;
	compiler->current_block = NULL;
	compiler->current_line_number = 1;
	compiler->input_mode = DKC_FILE_INPUT_MODE;
#ifdef EUC_SOURCE
	compiler->source_encoding = EUC_SOURCE;
#else
#ifdef SHIFT_JIS_SOURCE
	compiler->source_encoding = SHIFT_JIS_SOURCE;
#else
#ifdef UTF_8_SOURCE
	compiler->source_encoding = UTF_8_SOURCE;
#else
	fprintf(stderr, "source encoding is not defined\n");
	exit(1);
#endif
#endif
#endif
	dkc_set_current_compiler(compiler);

	return compiler;
}

DVM_Executable *DKC_compile(DKC_Compilier *compiler, FILE *fp)
{
	extern FILE *yyin;
	DVM_Executable *exe;

	compiler->currert_line_number = 1;

	yyin = fp;

	exe = do_compile(compiler);

	dkc_reset_string_literal_buffer();

	return exe;
}