#include <stdio.h>
#include "yaplang.h"

Block *yap_create_block(StatementList *statement_list)
{
    printf("Create Block\n");
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

Statement *
crb_create_for_statement(Expression *init, Expression *cond,
                         Expression *post, Block *block)
{
    Statement *st;

    st = alloc_statement(FOR_STATEMENT);
    st->u.for_s.init = init;
    st->u.for_s.condition = cond;
    st->u.for_s.post = post;
    st->u.for_s.block = block;

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

Statement *yap_create_while_statement(Expression *cond, Block *block)
{
	Statement *st;

	st = alloc_statement(WHILE_STATEMENT);
	st->u.while_s.cond = cond;
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

IdentifierList *
crb_create_global_identifier(char *identifier)
{
    IdentifierList      *i_list;

    i_list = crb_malloc(sizeof(IdentifierList));
    i_list->name = identifier;
    i_list->next = NULL;

    return i_list;
}

IdentifierList *yap_create_global_identifier(char *identifier)
{
	IdentifierList *i_list;

	i_list = yap_malloc(sizeof(IdentifierList));
	i_list->name = identifier;
	i_list->next = NULL;

	return i_list;
}

IdentifierList *
crb_chain_identifier(IdentifierList *list, char *identifier)
{
    IdentifierList *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = crb_create_global_identifier(identifier);

    return list;
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

	st = alloc_statement(EXPRESSION_SATEMENT);
	st->u.expression_s = expression;

	return st;
}

Expression *yap_alloc_expression(ExpressionType type)
{
	Expression *exp;

	exp = yap_malloc(sizeof(Expression));
	exp->type = type;
	exp->line_number = yap_get_current_interpreter()->current_line_number;

	return exp;
}

Expression *yap_create_null_expression(void)
{
	Expression *exp;

	exp = yap_alloc_expression(NULL_EXPRESSION);

	return exp;
}

Expression *yap_create_boolean_expression()
{
	Expression *exp;

	exp = yap_alloc_expression(BOOLEAN_EXPRESSION);

	return exp;
}