#include "diksamc.h"

static DKC_Compiler *st_current_compiler;

DKC_Compiler *dkc_get_current_compiler(void)
{
	return st_current_compiler;
}

void dkc_set_current_compiler(DKC_Compiler *compiler)
{
	st_current_compiler = compiler;
}

void *dkc_malloc(size_t size)
{
	void *p;
	DKC_Compiler *compiler;

	compiler = dkc_get_current_compiler();
	p = MEM_storage_malloc(compiler->compile_storage, size);

	return p;
}