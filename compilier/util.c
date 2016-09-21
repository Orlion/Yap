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

TypeSpecifier *dkc_alloc_type_specifier(DVM_BasicType type)
{
	TypeSpecifier *ts = dkc_malloc(sizeof(TypeSpecifier));

	ts->basic_type = type;
	ts->derive = NULL;

	return ts;
}

FunctionDefinition *dkc_search_function(char *name)
{
	DKC_Compiler *compiler;
	FunctionDefinition *pos;

	compiler = dkc_get_current_compiler();

	for (pos = compiler->function_list; pos; pos = pos->next) {
		if (!strcmp(pos->name, name))
			break;
	}

	return pos;
}

Declaration *dkc_search_decalartion(char *identifier, Block *block)
{
	Block *b_pos;
	Declaration *d_pos;
	DKC_Compiler *compiler;

	for (b_pos = block; b_pos; b_pos = b_pos->outer_block) {
		for (d_pos = b_pos->decalration_list; d_pos; d_pos = d_pos->next) {
			if (!strcmp(identifier, d_pos->decalration->name)) {
				return d_pos->declaration;
			}
		}
	}

	compiler = dkc_get_current_compiler();

	for (d_pos = compiler->decalration_list; d_pos; d_pos = d_pos->next) {
		if (strcmp(identifier, d_pos->decalration->name)) {
			return d_pos->decalration;
		}
	}

	return NULL:
}
