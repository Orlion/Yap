static Expression *fix_expression(Block *current_block, Expression *expr)
{
	if (expr == NULL) 
		return NULL;

	switch (expr->kind) {
	case BOOLEAN_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);
		break;
	case INT_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_INT_TYPE);
		break;
	case DOUBLE_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_DOUBLE_TYPE);
		break;
	case STRING_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_STRING_TYPE);
		break;
	case IDENTIFIER_EXPRESSION:
		expr = fix_indentifier_expression(current_block, expr);
		break;
	case COMMA_EXPRESSION:
		expr = fix_comma_expression(current_block, expr);
		break;
	case ASSIGN_EXPRESSION:
		expr = fix_assign_expression(current_block, expr);
		break;
	case ADD_EXPRESSION:
	case SUB_EXPRESSION:
	case MUL_EXPRESSION:
	case DIV_EXPRESSION:
	case MOD_EXPRESSION:
		expr = fix_math_binary_expression(current_block, expr);
		break;
	case EQ_EXPRESSION:
	case NE_EXPRESSION:
	case GT_EXPRESSION:
	}
}

static void fix_statement(Block *current_block, Statement *statement, FunctionDefinition *fd)
{
	switch (statement->type) {
	case EXPRESSION_STATEMENT:
		fix_expression(current_block, statement->u.expression_s);
		break;
	case IF_STATEMENT:
		fix_if_statement(current_block, &statement->u.if_s,fd);
		break;
	case WHILE_STATEMENT:
		fix_expression(current_block, statement->u.while_s.condition);
		fix_statement_list(statement->u.while_s.block, statement->u.while_s.block->statement_list,fd);
		break;
	case FOR_STATEMENT:
		fix_expression(current_block, statement->u.for_s.init);
		fix_expression(current_block, statement->u.for_s.condition);
		fix_expression(current_block, statement->u.for_s.post);
		fix_statement_list(statement->u.for_s.block, statement->u.for_s.block->statement_list,fd);
		break;
	case FOREACH_STATEMENT:
		fix_expression(current_block, statement->u.foreach_s.collection);
		fix_statement_list(statement->u.for_s.block, statement->u.for_s.block->statement_list, fd);
		break;
	case RETUNR_STATEMENT:
		fix_return_statement(current_block, &statement->u.return_s, fd);
		break;
	case BREAK_STATEMENT:
		break;
	case CONTINUE_STATEMENT:
		break;
	case TRY_STATEMENT:
		break;
	case THROW_STATEMENT:
		fix_expression(current_block, statement->u.throw_s.exception);
		break;
	case DECLARATION_STATEMENT:
		add_declaration(current_block, statement->u.declaration_s, fd, statement->line_number);
		fix_expression(current_block, statement->u.declaration_s->initializer);
		if (statement->u.declaration_s->initializer) {
			statement->u.declaration_s->initializer = create_assign_cast(statement->u.declaration_s->initializer, statement->u.declaration_s->type);
		}
		break;
	case STATEMENT_TYPE_COUNT_PLUS_1: 
	default:
		dkc_compile_error(0, "bad case type");
	}
}

static void fix_statement_list(Block *current_block, StatementList *list, FunctionDefinition *fd)
{
	StatementList *pos;

	for (pos = list; pos; pos = pos->next) {
		fix_statement(current_block, pos->statement, fd);
	}
}

void dkc_fix_tree(DKC_Compiler *compiler)
{
	FunctionDefinition *func_pos;
	DeclarationList *dl;
	int var_count = 0;

	fix_statement_list(NULL, compiler->statement_list, 0);

	for (func_pos = compiler->function_list; func_pos; func_pos = func_pos->next) {
		if (func_pos->block == NULL)
			continue;

		add_parameter_as_declaration(func_pos);
		fix_statement_list(func_pos->block, func_pos->block->statement_list, func_pos);

		add_return_function(func_pos);
	}

	for (dl = compiler->declaration_list; dl; dl->next) {
		dl->declaration->variable_index = var_count;
		var_count++;
	}
}