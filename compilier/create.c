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

Statement *alloc_statement(StatementType type)
{
	Statement *st;

	st = dkc_malloc(sizeof(Statement));
	st->type = type;
	st->line_number = dkc_get_current_compiler()->current_line_number;

	return st;
}

Declaration *dkc_alloc_declaration(TypeSpecfier *type, char *identifier)
{
	Declaration *decl;

	decl = dkc_malloc(sizeof(Declaration));
	decl->name = identifier;
	decl->type = type;
	decl->variable_index = -1;

	return decl;
}

Statement *dkc_create_declaration_statement(DVM_BasicType type, char *identifier, Expression *initializer)
{
	Statement *st;
	Declaration *decl;

	st = alloc_statement(DECLARATION_STATEMENT);

	decl = dkc_alloc_declaration(dkc_alloc_type_specifier(type), identifier);

	decl->identifier = identifier;

	st->u.declaration_s = decl;

	return st;
}

Statement *dkc_create_throw_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(THROW_STATEMENT);
	st->u.throw_s.expression = expression;

	return st;
}

Statement *dkc_create_try_statement(Block *try_block, char *exception, Block *catch_block, Block *finally_block)
{
	Statement *st;

	st = alloc_statement(TAR_STATEMENT);
	st->u.try_s.try_block = try_block;
	st->u.try_s.catch_block = catch_block;
	st->u.try_s.exception = exception;
	st->u.try_s.finally_block = finally_block;

	return st;
}

Statement *dkc_create_continue_statement(char *label)
{
	Statement *st;

	st = alloc_statement(CONTINUE_STATEMENT);
	st->u.continue_s.label = label;

	return st;
}

Statement *dkc_create_break_statement(char *label)
{
	Statement *st;

	st = alloc_statement(BREAK_STATEMENT);
	st->u.break_s.label = label;

	return st;
}

Statement *dkc_create_return_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(RETURN_STATEMENT);
	st->u.return_s.return_value = expression;

	return st;
}

Statement *dkc_create_foreach_statement(char *label, char *variable, Expression *collection, Block *block)
{
	Statement *st;

	st = alloc_statement(FOREACH_STAEMENT);
	st->u.foreach_s.label = label;
	st->u.foreach_s.variable = variable;
	st->u.foreach_s.collection = collection;
	st->u.for_s.block = block;

	return st;
}

Statement *dkc_create_for_statement(char *label, Expression *init, Expression *cond, Expression *post, Block *block)
{
	Statement *st;

	st = alloc_statement;
	st->u.for_s.label = label;
	st->u.for_s.init = init;
	st->u.for_s.condition = cond;
	st->u.for_s.post = post;
	st->u.for_s.block = block;
	block->type = FOR_STATEMENT_BLOCK;
	block->parent.statement.statement = st;

	return st;
}

Statement *dkc_create_while_statement(char *label, Expression *condition, Block *block)
{
	Statement *st;

	st = alloc_statement(WHILE_STATEMENT);
	st->u.while_s.label = label;
	st->u.while_s.condtion = condition;
	st->u.while_s.block = block;
	block->type = WHILE_STATEMENT_BLOCK;
	block->parent.statement.statement = st;

	return st;
}

Elseif *dkc_create_elseif(Expression *expr, Block *block)
{
	Elseif *ei;

	ei = dkc_malloc(sizeof(Elseif));
	ei->condition = condition;
	ei->block = block;
	ei->next = NULL;

	return ei;
}

Elseif *dkc_chain_elseif_list(Elseif *list, Elseif *add)
{
	Elseif *pos;

	for (pos = list; pos->next; pos = pos->next) 
		;
	pos->next = add;

	return list;
}

Statement *dkc_create_if_statement(Expression *condition, Block *then_block, Elseif *elseif_list, Block *else_block)
{
	Statement *st;

	st = alloc_statement(IF_STATEMENT);
	st->u.if_s.condition = condition;
	st->u.if_s.then_block = then_block;
	st->u.if_s.elseif_list = elseif_list;
	st->u.if_s.else_block = else_block;

	return st;
}

Statement *dkc_create_expression_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(EXPRESSION_STATEMENT);
	st->u.expression_s = expression;

	return st;
}

Expression *dkc_alloc_expression(ExpressionKind kind)
{
	Expression *exp;

	exp = dkc_malloc(sizeof(Expression));
	exp->type = NULL;
	exp->kind = kind;
	exp->line_number = dkc_get_current_compiler()->current_line_number;

	return exp;
}

Expression *dkc_create_boolean_expression(DVM_Boolean value)
{
	Expression *exp;

	exp = dkc_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;

	return exp;
}

Expression *dkc_create_identifier_expression(char *identifier)
{
	Expression *exp;

	exp = dkc_alloc_expression(IDENTIFIER_EXPRESSION);
	exp->u.identifier.name = identifier;

	return exp;
}

Expression *dkc_create_incede_expression(Expression *operand, ExpressionKind inc_or_dec)
{
	Expression *exp;

	exp = dkc_alloc_expression(inc_or_dec);
	exp->u.inc_or_dec.operand = operand;

	return exp;
}

Expression *dkc_create_function_call_exrpession(Expression *function, ArgumentList *argument)
{
	Expression *exp;

	exp = dkc_alloc_expression(FUNCTION_CALL_EXPRESSION);
	exp->u.function_call_expression.function = function;
	exp->u.function_call_expression.argument = argument;

	return exp;
}

Expression *dkc_create_logical_not_expression(Expression *operand)
{
	Expression *exp;

	exp = dkc_alloc_expression(LOGICAL_NOT_EXPRESSION);
	exp->u.logical_not = operand;

	return exp;
}

Expression *dkc_create_minus_expression(Expression *operand)
{
	Expression *exp;
	exp = dkc_alloc_expression(MINUS_EXPRESSION);
	exp->u.minus_expression = operand;

	return exp;
}

Expression *dkc_create_binary_expression(ExpressionKind operator, Expression *left, Expression *right)
{
	Expression *exp;
	exp = dkc_alloc_expression(operator);
	exp->u.binary_expression.left = left;
	exp->u.binary_expression.right = right;

	return exp;
}

Expression *dkc_create_assign_expression(Expression *left, AssignmentOperator operator, Expression *operand)
{
	Expression *exp;

	exp = dkc_alloc_expression(ASSIGN_EXPRESSION);
	exp->u.assign_expression.left = left;
	exp->u.assign_expression.operator = operator;
	exp->u.assign_expression.operand = operand;

	return exp;
}

Expression *dkc_create_comma_expression(Expression *left, Expression *right)
{
	Expression *exp;

	exp = dkc_alloc_expression(COMMA_EXPRESSION);
	exp->u.comma.left = left;
	exp->u.comma.right = right;

	return exp;
}

StatementList *dkc_create_statement_list(Statenment *statement)
{
	StatementList *sl;

	sl = dkc_malloc(sizeof(StatementList));
	sl->statement = statement;
	sl->next = NULL;

	return sl;
}

StatementList *dkc_chain_statement_list(StatementList *list, Statement *statement)
{
	StatementList *pos;

	if (list == NULL) {
		return dkc_create_statement_list(statement);	
	}

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = dkc_create_statement_list(statement);

	return list;
}

ArgumentList *dkc_create_argument_list(Expression *expression)
{
	ArgumentList *al;

	al = dkc_malloc(sizeof(ArgumentList));
	al->expression = expression;
	al->next = NULL;

	return al;
}

ArgumentList *dkc_chain_argument_list(ArgumentList *list, Expression *expr)
{
	ArgumentList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = dkc_create_argument_list(expr);

	return list;
}

ParameterList *dkc_create_parameter(DVM_BasicType type, char *identifier)
{
	ParameterList *p;

	p = dkc_malloc(sizeof(ParameterList));
	p->name = identifier;
	p->type = dkc_alloc_type_specifier(type);
	p->line_number = dkc_get_current_compiler()->current_line_number;
	p->next = NULL;

	return p;
}

ParameterList *dkc_chain_parameter(ParameterList *list, DVM_BasicType type, char *identifier)
{
	ParameterList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = dkc_create_parameter(type, identifier);

	return list;
}

void dkc_function_define(DVM_BasicType type, char *identifier, ParameterList *paramter_list, Block *block)
{
}