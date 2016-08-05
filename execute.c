#include "yaplang.h"

static StatementResult execute_expression_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatemetnResult result;
    YAP_Value v;

    result.type = NORMAL_STATEMNET_RESULT;

    v = yap_eval_expression(inter, env, statement->u.expression_s);
    if (v.type == YAP_STRING_VALUE) {
        yap_release_string(v.u.string_value);
    }

    return result;
}

static StatementResult execute_global_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    IdentifierList *pos;
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;

    if (env == NULL) {
        yap_runtime_error(statement->line_number, GLOBAL_STATEMENT_INT_TOPLEVEL_ERR, MESSAGE_ARGUMENT_END);
    }
    for (pos = statement->u.global_s.identifier_list; pos; pos->next) {
        GlobalVariableRef *ref_pos;
        GlobalVariableRef *new_ref;
        Variable *variable;
        for (ref_pos = env->global_variable; ref_pos; ref_pos = ref_pos->next) {
            if (!strcmp(ref_pos->variable->name, pos->name))
                goto NEXT_IDENTIFIER;    
        }
        variable = yap_search_global_variable(inter, pos->name);
        if (variable == NULL) {
            yap_runtime_error(statement->line_number, GLOBAL_VARIABLE_NOT_FOUND_ERR, STRING_MESSAGE_ARGUMENT, "name", pos->name, MESSAGE_ARGUMENT_END);
        }
        new_ref = MEM_malloc(sizeof(GlobalVariableRef));
        new_ref->variable = variable;
        new_ref->next = env->global_variable;
        env->global_variable = new_ref;
      NEXT_IDENTIFIER:
        ;
    }

    return result;
}

static StatementResult
execute_if_statement(CRB_Interpreter *inter, LocalEnvironment *env,
                     Statement *statement)
{
    StatementResult result;
    CRB_Value   cond;

    result.type = NORMAL_STATEMENT_RESULT;
    cond = crb_eval_expression(inter, env, statement->u.if_s.condition);
    if (cond.type != CRB_BOOLEAN_VALUE) {
        crb_runtime_error(statement->u.if_s.condition->line_number,
                          NOT_BOOLEAN_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    DBG_assert(cond.type == CRB_BOOLEAN_VALUE, ("cond.type..%d", cond.type));

    if (cond.u.boolean_value) {
        result = crb_execute_statement_list(inter, env,
                                            statement->u.if_s.then_block
                                            ->statement_list);
    } else {
        CRB_Boolean elsif_executed;
        result = execute_elsif(inter, env, statement->u.if_s.elsif_list,
                               &elsif_executed);
        if (result.type != NORMAL_STATEMENT_RESULT)
            goto FUNC_END;
        if (!elsif_executed && statement->u.if_s.else_block) {
            result = crb_execute_statement_list(inter, env,
                                                statement->u.if_s.else_block
                                                ->statement_list);
        }
    }

  FUNC_END:
    return result;
}

static StatementResult execute_elseif(YAP_Interpreter *inter, LocalEnvironment *env, Elseif *elseif_list, YAP_Boolean *executed)
{
    StatementResult result;
    YAP_Value cond;
    Elseif *pos;

    *executed = YAP_FALSE;
    result.type = NORMAL_STATEMENT_RESULT;
    for (pos = elseif_list; pos; pos->next) {
        cond = yap_eval_expression(inter, env, pos->condtion);
        if (cond.type != YAP_BOOLEAN_VALUE) {
            yap_runtime_error();
        }
        if (cond.u.boolean_value) {
            result = yap_execute_statement_list(inter, env, pos->block->statement_list);
            *executed = YAP_TRUE;
            if (result.type != NORMAL_STATEMENT_RESULT)
                goto FUNC_END;
        }
    }
  FUNC_END:
    return result;
}

static StatementResult execute_if_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult result;
    YAP_Value cond;

    result.type = NORMAL_STATEMENT_RESULT;
    cond = yap_eval_expression(inter, env, statement->u.if_s.condition);
    if (cond.type != YAP_BOOLEAN_VALUE) {
        yap_runtime_error();
    }

    if (cond.u.boolena_value) {
        result = yap_execute_statement_list(inter, env, statment->u.if_s.then_block->statement_list);
    } else {
        YAP_Boolean elseif_executed;
        result = execute_elseif(inter, env, statement->u.if_s.elseif_list, &elseif_executed);
        if (result.type != NORMAL_STATEMENT_RESULT) 
            goto FUNC_END;
        if (!elseif_executed && statement->u.if_s.else_block) {
            result = yap_execute_statement_list(inter, env, statement->u.if_s.else_block->statement_list);
        }
    }
  FUNC_END:
    return result;
}

static Statement execute_while_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementReuslt result;
    YAP_Value cond;

    result.type = NORMAL_STATEMENT_RESULT;
    for (;;) {
        cond = yap_eval_expression(inter, env, statement->u.while_s.condition);
        if (cond.type != YAP_BOOLEAN_VALUE) {
            yap_runtime_error();
        }

        if (!cond.u.boolean_value) 
            break;

        result = yap_execute_statement_list(inter, env, statement->u.while_s.block->statement_list);
        if (result.type == RETURN_STATEMENT_RESULT) {
            break;
        } else if (result.type == BREAK_STATEMENT_RESULT) {
            result.type = NORMAL_STATEMENT_RESULT;
            break;
        }
    }

    return result;
}

static StatementResult execute_for_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult result;
    YAP_Value       cond;

    result.type = NORMAL_STATEMENT_RESULT;

    if (statement->u.for_s.init) {
        yap_eval_expression(inter, env, statement->u.for_s.init);
    }
    for (;;) {
        if (statement->u.for_s.condition) {
            cond = yap_eval_expression(inter, env, statement->u.for_s.condition);
            if (cond.type != YAP_BOOLEAN_VALUE) {
                yap_runtime_error();
            }

            if (!cond.u.boolean_value)
                break;
        }
        result = yap_execute_statement_list(inter, env, statement->u.for_s.block->statement_list);
        if (result.type == RETURN_STATEMENT_RESULT) {
            break;
        } else if (result.type == BREAK_STATEMENT_RESULT) {
            result.type == NORMAL_STATEMENT_RESULT;
            break;
        }

        if (statement->u.for_s.post) {
            yap_eval_expression(inter, env, statement->u.for_s.post);
        }
    }
}

static StatementResult execute_return_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult result;

    result.type = RETURN_STATEMENT_RESULT;
    if (statement->u.return_s.return_value) {
        result.u.return_value = yap_eval_expression(inter, env, statement->u.return_s.return_value);
    } else {
        result.u.return_value.type = YAP_NULL_VALUE;
    }

    return result;
}

static StatementResult executed_break_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult reuslt;

    result.type = BREAK_STATEMENT_RESULT;

    return result;
}

static StatementResult execute_continue_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult result;

    result.type = CONTINUE_STATEMENT_RESULT;

    return result;
}

static StatementResult execute_statement(YAP_Interpreter *inter, LocalEnvironment *env, Statement *statement)
{
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;

    switch (statement->type) {
    case EXPRESSION_STATEMENT:
        result = execute_expression_statement(inter, env, statement);
        break;
    case GLOBAL_STATEMENT:
        result = execute_global_statement(inter, env, statement);
        break;
    case IF_STATEMENT:
        result = execute_if_statement(inter, env, statement);
        break;
    case WHILE_STATEMENT:
        result = execute_while_statement(inter, env, statement);
        break;
    case FOR_STATEMENT:
        result = execute_for_statement(inter, env, statement);
        break;
    case RETURN_STATEMENT:
        result = execute_return_statement(inter, env, statement);
        break;
    case BREAK_STATEMENT:
        result = execute_break_statement(inter, env, statement);
        break;
    case CONTINUE_STATEMENT:
        result = execute_continue_statement(inter, env, statement);
        break;
    case STATEMENT_TYPE_COUNT_PLUS_1:
    default:
        printf("语句类型不存在");
    }

    return result;
}

StatementResult yap_execute_statement_list(YAP_Interpreter *inter, LocalEnvironment *env, StatementList *list)
{
    StatementList *pos;
    StatementResult result;

    result.type = NORMAL_STATEMENT_RESULT;
    for (pos = list; pos; pos = pos->next) {
        result = execute_statement(inter, env, pos->statement);
        if (result.type != NORMAL_STATEMENT_RESULT)
            goto FUNC_END;
    }

  FUNC_END:
    return result;
}