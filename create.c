#include <stdio.h>
#include "yaplang.h"

void yap_function_define(char *identifier, ParameterList *parameter_list, Block *block)
{
	FunctionDefinition *f;
	YAP_Interpreter *inter;

	if (yap_search_function(identifier)) {
		/* yap_compile_error(FUNCTION_MULTIPLE_DEFINE_ERR, STRING_MESSAGE_ARGUMENT, "name", identifier, MESSAGE_ARGUMENT_END); */
		printf("编译错误:函数%s未定义", identifier);

		return;
	}

	inter = yap_get_current_interpreter();

	f = yap_malloc(sizeof(FunctionDefinition));
	f->name = identifier;
	f->type = YAP_FUNCTION_DEFINITION;
	f->u.yap_f.parameter = parameter_list;
	f->u.yap_f.block = block;
	f->next = inter->function_list;
	inter->function_list = f;
}

StatementList *yap_create_statement_list(Statement *statement)
{
    StatementList *sl;

    sl = yap_malloc(sizeof(StatementList));
    sl->statement = statement;
    sl->next = NULL;

    return sl;
}

StatementList *yap_chain_statement_list(StatementList *list, Statement *statement)
{
	StatementList *pos;

	if (list == NULL)
		return yap_create_statement_list(statement);

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = yap_create_statement_list(statement);

	return list;
}

Block *yap_create_block(StatementList *statement_list)
{
    Block *block;

    block = yap_malloc(sizeof(Block));
    block->statement_list = statement_list;

    return block;
}

static Statement *alloc_statement(StatementType type)
{
    Statement *st;

    st = yap_malloc(sizeof(Statement));
    st->type = type;
    st->line_number = yap_get_current_interpreter()->current_line_number;

    return st;
}

Statement *yap_create_continue_statement(void)
{
    return alloc_statement(CONTINUE_STATEMENT);
}

Statement *yap_create_break_statement(void)
{
    return alloc_statement(BREAK_STATEMENT);
}

Statement *yap_create_return_statement(Expression *expression)
{
    Statement *st;

    st = alloc_statement(RETURN_STATEMENT);
    st->u.return_s.return_value = expression;

    return st;
}

Statement *yap_create_for_statement(Expression *init, Expression *cond, Expression *post, Block *block)
{
	Statement *st;

	st = alloc_statement(FOR_STATEMENT);
	st->u.for_s.init = init;
	st->u.for_s.condition = cond;
	st->u.for_s.post = post;
	st->u.for_s.block = block;

	return st;
}

Statement *yap_create_while_statement(Expression *condition, Block *block)
{
	Statement *st;

	st = alloc_statement(WHILE_STATEMENT);
	st->u.while_s.condition = condition;
	st->u.while_s.block = block;

	return st;
}

Statement *yap_create_if_statement(Expression *condition, Block *then_block, Elseif *elseif_list, Block *else_block)
{
	Statement *st;
	st = alloc_statement(IF_STATEMENT);
	st->u.if_s.condition = condition;
	st->u.if_s.then_block = then_block;
	st->u.if_s.elseif_list = elseif_list;
	st->u.if_s.else_block = else_block;

	return st;
}

Elseif *yap_chain_elseif_list(Elseif *list, Elseif *add)
{
	Elseif *pos;
	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = add;

	return list;
}

Elseif *yap_create_elseif(Expression *expr, Block *block)
{
    Elseif *ei;

    ei = yap_malloc(sizeof(Elseif));
    ei->condition = expr;
    ei->block = block;
    ei->next = NULL;

    return ei;
}

Expression *yap_alloc_expression(ExpressionType type)
{
    Expression  *exp;

    exp = yap_malloc(sizeof(Expression));
    exp->type = type;
    exp->line_number = yap_get_current_interpreter()->current_line_number;

    return exp;
}

Expression *yap_create_assign_expression(char *variable, Expression *operand)
{
	Expression *exp;

	exp = yap_alloc_expression(ASSIGN_EXPRESSION);
	exp->u.assign_expression.variable = variable;
	exp->u.assign_expression.operand = operand;

	return exp;
}

IdentifierList *yap_create_global_identifier(char *identifier)
{
	IdentifierList *i_list;

	i_list = yap_malloc(sizeof(IdentifierList));
	i_list->name = identifier;
	i_list->next = NULL;

	return i_list;
}

IdentifierList *yap_chain_identifier(IdentifierList *list, char *identifier)
{
	IdentifierList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = yap_create_global_identifier(identifier);

	return list;
}

Statement *yap_create_global_statement(IdentifierList *identifier_list)
{
	Statement *st;

	st = alloc_statement(GLOBAL_STATEMENT);
	st->u.global_s.identifier_list = identifier_list;

	return st;
}

Statement *yap_create_expression_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(EXPRESSION_STATEMENT);
	st->u.expression_s = expression;

	return st;
}

Expression *yap_create_null_expression(void)
{
	Expression *exp;

	exp = yap_alloc_expression(NULL_EXPRESSION);

	return exp;
}

Expression *yap_create_boolean_expression(YAP_Boolean value)
{
	Expression *exp;

	exp = yap_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;

	return exp;
}

Expression *yap_create_identifier_expression(char *identifier)
{
	Expression *exp;

	exp = yap_alloc_expression(IDENTIFIER_EXPRESSION);
	exp->u.identifier = identifier;

	return exp;
}


Expression *yap_create_function_call_expression(char *func_name, ArgumentList *argument)
{
	Expression *exp;

	exp = yap_alloc_expression(FUNCTION_CALL_EXPRESSION);
	exp->u.function_call_expression.identifier = func_name;
	exp->u.function_call_expression.argument = argument;

	return exp;
}

Expression *yap_create_minus_expression(Expression *operand)
{
	if (operand->type == INT_EXPRESSION || operand->type == DOUBLE_EXPRESSION) {
		/* YAP_Value	v; */
		/* v = yap_eval_minus_expression(yap_get_current_interpreter(), NULL, operand); */

		/* *operand = convert_value_to_expression(&v); */

		return operand;
	} else {
		Expression 	*exp;
		exp = yap_alloc_expression(MINUS_EXPRESSION);
		exp->u.minus_expression = operand;

		return exp;
	}
}

Expression *yap_create_binary_expression(ExpressionType operator, Expression *left, Expression *right)
{
	if ((left->type == INT_EXPRESSION || left->type == DOUBLE_EXPRESSION) && (right->type == INT_EXPRESSION || right->type == DOUBLE_EXPRESSION)) {
		/* YAP_Value v; */
		/* v = yap_eval_binary_expression(yap_get_current_interpreter(), NULL, operator, left, right); */
		/* *left = convert_value_to_expression(&v);*/

		return left;
	} else {
		Expression *exp;
		exp = yap_alloc_expression(operator);
		exp->u.binary_expression.left = left;
		exp->u.binary_expression.right = right;

		return exp;
	}
}

ArgumentList *yap_create_argument_list(Expression *expression)
{
	ArgumentList *al;

	al = yap_malloc(sizeof(ArgumentList));
	al->expression = expression;
	al->next = NULL;

	return al;
}

ArgumentList *yap_chain_argument_list(ArgumentList *list, Expression *expr)
{
	ArgumentList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = yap_create_argument_list(expr);

	return list;
}

ParameterList *yap_create_parameter(char *identifier)
{
	ParameterList *p;

	p = yap_malloc(sizeof(ParameterList));
	p->name = identifier;
	p->next = NULL;

	return p;
}

ParameterList *yap_chain_parameter(ParameterList *list, char *identifier)
{
	ParameterList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = yap_create_parameter(identifier);

	return list;
}

