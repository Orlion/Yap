#include <stdlib.h>
#include "MEM.h"
#include "diksamc.h"

static DVM_Executable *do_compile(DKC_Compiler *compiler)
{
	extern int yyparse(void);
	DVM_Executable *exe;

	dkc_set_current_compiler(compiler);
	if (yyparse()) {
		fprintf(stderr, "Error\n");
		exit(1);
	}
	dkc_fix_tree(compiler);				/* 修正分析树 */
	/* exe = dkc_generate(compiler); */

	return exe;
}

DKC_Compiler *DKC_create_compiler(void)
{
	MEM_Storage storage;
	DKC_Compiler *compiler;

	storage = MEM_open_storage(0);
	compiler = MEM_storage_malloc(storage, sizeof(struct DKC_Compiler_tag));
	compiler->compile_storage = storage;
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
	/* dkc_set_current_compiler(compiler); */
 
	return compiler;
}

DVM_Executable *DKC_compile(DKC_Compiler *compiler, FILE *fp)
{
	extern FILE *yyin;
	DVM_Executable *exe;

	/* compiler->currert_line_number = 1; */

	yyin = fp;

	exe = do_compile(compiler);

	return exe;
}

void dkc_compile_error(int line_number, char *msg)
{
	fprintf(stderr, "[ERROR]%s [line in :%d]\n", msg, line_number);
	exit(1);
}

void yyerror()
{
	extern char *yytext;
	char msg[100];
	sprintf(msg, "syntax error, unexpected '%s'", yytext);
	dkc_compile_error(dkc_get_current_compiler()->current_line_number, msg);
}