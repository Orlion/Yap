Expression *dkc_alloc_expression(ExpressionKind kind)
{
	Expression *exp;

	exp = dkc_malloc(sizeof(Expression));
	exp->type = NULL;
	exp->kind = kind;
	exp->line_number = dkc_get_current_compiler()->current_line_number;

	return exp;
}

Block *dkc_open_block(void)
{
	Block *new_block;

	DKC_Compiler *compiler = dkc_get_current_compiler();
	new_block = dkc_malloc(sizeof(Blokc));
	new_blokc->type = UNDEFINED_BLOCK;
	new_block->outer_block = compiler->current_block;
	new_block->declaration_list = NULL;
	compiler->current_block = new_block;

	return new_block;
}

Block *dkc_close_block(Block *block, StatementList *statement_list)
{
	DKC_Compiler *compiler = dkc_get_current_compiler();
	block->statement_list = statement_list;
	compiler->current_block = block->outer_block;

	return block;
}