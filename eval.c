static YAP_Value eval_boolean_expression(YAP_Value boolean_value)
{
    YAP_Value v;

    v.type = YAP_BOOLEAN_VALUE;
    v.u.boolean_value = boolean_value;

    return v;
}

static YAP_Value eval_int_expression(int int_value)
{
    YAP_Value v;

    v.type = YAP_INT_VALUE;
    v.u.int_value = int_value;

    return v;
}

static YAP_Value eval_double_expression(double double_value)
{
    YAP_Value v;

    v.type = YAP_DOUBLE_VALUE;
    v.u.double_value = double_value;

    return v;
}

static YAP_Value eval_string_expression(YAP_Interpreter *inter, char *string_value)
{
    YAP_Value v;

    v.type = YAP_STRING_VALUE;
    v.u.string_value = yap_literal_to_yap_string(inter, string_value);

    return v;
}

static void release_if_string(YAP_Value *v)
{
    if (v->type == YAP_STRING_VALUE) {
        yap_release_string(v->i.string_value);
    }
}

static void refer_if_string(YAP_Value *v)
{
    if (v->type == YAP_STRING_VALUE) {
        yap_refer_string(v->u.string_value);
    }
}

static Variable *search_global_variable_from_env(YAP_Interpreter *inter, LocalEnvironment *env, char *name)
{
    GlobalVariableRef *pos;

    if (env == NULL) {
        return yap_search_global_variable(inter, name);
    }

    for (pos = env->global_variable; pos; pos = pos->next) {
        if (!strcmp(pos->variable_name, name)) {
            return pos->variable;
        }
    }

    return NULL;
}

static YAP_Value eval_identifier_expression(YAP_Interpreter *inter, LocalEnvironment *env, Expression *expr)
{
    YAP_Value v;
    Variable *vp;

    vp = yap_search_local_variable(env, expr->u.identifier);
    if (vp != NULL) {
        v = vp->value;
    } else {
        vp = search_global_variable_from_env(inter, env, expr->u.identifier);
        if (vp != NULL) {
            v = vp->value;
        } else {
            char msg[100];
            sprintf(msg, "没找到变量-%s", expr->u.identifier);
            yap_runtime_error(msg);
        }
    }

    refer_if_string(&v);

    return v;
}

static YAP_VALUE eval_assign_expression(YAP_Interpreter *inter, LocalEnvironment *env, char *identifier, Expression *expression)
{
    YAP_Value v;
    Variable  *left;

    v = eval_expression(inter, env, expression);

    left = yap_search_local_variable(env, identifier);
    if (left == NULL) {
        left = search_global_variable_from_env(inter, env, identifier);
    }
    if (left != NULL) {
        release_if_string(&left->value);
        left->value = v;
        refer->if_string(&v);
    } else {
        if (env != NULL) {
            yap_add_local_variable(env, identifier, &v);
        } else {
            YAP_add_global_variable(inter, identifier, &v);
        }
        refer_if_string(&v);
    }

    return v;
}

static void eval_binary_int(YAP_Interpreter *inter, ExpressionType operator, int left, int right, YAP_Value *result, int line_number)
{
    char msg[100];
    sprintf(msg, "未知的ExpressionType-%d", operator);
    if (dkc_is_math_operator(operator)) {
        result->type = YAP_INT_VALUE;
    } else if (dkc_is_compare_operator(operator)) {
        result->type = YAP_BOOLEAN_VALUE;
    } else {
        yap_runtime_error(msg);
    }

    switch (operator) {
    case BOOLEAN_EXPRESSION:    /* FALLTHRU */
    case INT_EXPRESSION:        /* FALLTHRU */
    case DOUBLE_EXPRESSION:     /* FALLTHRU */
    case STRING_EXPRESSION:     /* FALLTHRU */
    case IDENTIFIER_EXPRESSION: /* FALLTHRU */
    case ASSIGN_EXPRESSION:
        yap_runtime_error(msg);
        break;
    case ADD_EXPRESSION:
        result->u.int_value = left + right;
        break;
    case SUB_EXPRESSION:
        result->u.int_value = left - right;
        break;
    case MUL_EXPRESSION:
        result->u.int_value = left * right;
        break;
    case DIV_EXPRESSION:
        result->u.int_value = left / right;
        break;
    case MOD_EXPRESSION:
        result->u.int_value = left % right;
        break;
    case LOGICAL_AND_EXPRESSION:        /* FALLTHRU */
    case LOGICAL_OR_EXPRESSION:
        yap_runtime_error(msg);
        break;
    case EQ_EXPRESSION:
        result->u.boolean_value = left == right;
        break;
    case NE_EXPRESSION:
        result->u.boolean_value = left != right;
        break;
    case GT_EXPRESSION:
        result->u.boolean_value = left > right;
        break;
    case GE_EXPRESSION:
        result->u.boolean_value = left >= right;
        break;
    case LT_EXPRESSION:
        result->u.boolean_value = left < right;
        break;
    case LE_EXPRESSION:
        result->u.boolean_value = left <= right;
        break;
    case MINUS_EXPRESSION:              /* FALLTHRU */
    case FUNCTION_CALL_EXPRESSION:      /* FALLTHRU */
    case NULL_EXPRESSION:               /* FALLTHRU */
    case EXPRESSION_TYPE_COUNT_PLUS_1:  /* FALLTHRU */
    default:
        yap_runtime_error(msg);
    }
}

static void eval_binary_double(CRB_Interpreter *inter, ExpressionType operator, double left, double right, CRB_Value *result, int line_number)
{
    char msg[100];
    sprintf(msg, "未知的ExpressionType-%d", operator);
    if (dkc_is_math_operator(operator)) {
        result->type = YAP_DOUBLE_VALUE;
    } else if (dkc_is_compare_operator(operator)) {
        result->type = YAP_BOOLEAN_VALUE;
    } else {
        yap_runtime_error(msg);
    }

    switch (operator) {
    case BOOLEAN_EXPRESSION:    /* FALLTHRU */
    case INT_EXPRESSION:        /* FALLTHRU */
    case DOUBLE_EXPRESSION:     /* FALLTHRU */
    case STRING_EXPRESSION:     /* FALLTHRU */
    case IDENTIFIER_EXPRESSION: /* FALLTHRU */
    case ASSIGN_EXPRESSION:
        yap_runtime_error(msg);
        break;
    case ADD_EXPRESSION:
        result->u.double_value = left + right;
        break;
    case SUB_EXPRESSION:
        result->u.double_value = left - right;
        break;
    case MUL_EXPRESSION:
        result->u.double_value = left * right;
        break;
    case DIV_EXPRESSION:
        result->u.double_value = left / right;
        break;
    case MOD_EXPRESSION:
        result->u.double_value = fmod(left, right);
        break;
    case LOGICAL_AND_EXPRESSION:        /* FALLTHRU */
    case LOGICAL_OR_EXPRESSION:
        yap_runtime_error(msg);
        break;
    case EQ_EXPRESSION:
        result->u.int_value = left == right;
        break;
    case NE_EXPRESSION:
        result->u.int_value = left != right;
        break;
    case GT_EXPRESSION:
        result->u.int_value = left > right;
        break;
    case GE_EXPRESSION:
        result->u.int_value = left >= right;
        break;
    case LT_EXPRESSION:
        result->u.int_value = left < right;
        break;
    case LE_EXPRESSION:
        result->u.int_value = left <= right;
        break;
    case MINUS_EXPRESSION:              /* FALLTHRU */
    case FUNCTION_CALL_EXPRESSION:      /* FALLTHRU */
    case NULL_EXPRESSION:               /* FALLTHRU */
    case EXPRESSION_TYPE_COUNT_PLUS_1:  /* FALLTHRU */
    default:
        yap_runtime_error(msg);
    }
}

YAP_Value yap_eval_binary_expression(YAP_Interpreter *inter, LocalEnvironment *env, ExpressionType operator, Expression *left, Expression *right)
{
    YAP_Value   left_val;
    YAP_Value   right_val;
    YAP_Value   result;

    left_val = eval_expression(inter, env, left);
    right_val = eval_expression(inter, env, right);

    if (left_val.type == YAP_INT_VALUE && right_val.type == YAP_INT_VALUE) {
        eval_binary_int(inter, operator, left_val.u.int_value, right_val.u.int_value, &result, left->line_number);
    } else if (left_val.type == YAP_DOUBLE_VALUE && right_val.type == YAP_DOUBLE_VALUE) {
        eval_binary_double(inter, operator, left_val.u.double_value, right_val.u.double_value, &result, left->line_number);
    } else if (left_val.type == YAP_INT_VALUE
               && right_val.type == YAP_DOUBLE_VALUE) {
        left_val.u.double_value = left_val.u.int_value;
        eval_binary_double(inter, operator,
                           left_val.u.double_value, right_val.u.double_value,
                           &result, left->line_number);
    } else if (left_val.type == YAP_DOUBLE_VALUE
               && right_val.type == YAP_INT_VALUE) {
        right_val.u.double_value = right_val.u.int_value;
        eval_binary_double(inter, operator,
                           left_val.u.double_value, right_val.u.double_value,
                           &result, left->line_number);
    } else if (left_val.type == YAP_BOOLEAN_VALUE
               && right_val.type == YAP_BOOLEAN_VALUE) {
        result.type = YAP_BOOLEAN_VALUE;
        result.u.boolean_value
            = eval_binary_boolean(inter, operator,
                                  left_val.u.boolean_value,
                                  right_val.u.boolean_value,
                                  left->line_number);
    } else if (left_val.type == YAP_STRING_VALUE
               && operator == ADD_EXPRESSION) {
        char    buf[LINE_BUF_SIZE];
        YAP_String *right_str;

        if (right_val.type == YAP_INT_VALUE) {
            sprintf(buf, "%d", right_val.u.int_value);
            right_str = yap_create_yap_string(inter, MEM_strdup(buf));
        } else if (right_val.type == CRB_DOUBLE_VALUE) {
            sprintf(buf, "%f", right_val.u.double_value);
            right_str = yap_create_yap_string(inter, MEM_strdup(buf));
        } else if (right_val.type == CRB_BOOLEAN_VALUE) {
            if (right_val.u.boolean_value) {
                right_str = yap_create_yap_string(inter,
                                                      MEM_strdup("true"));
            } else {
                right_str = yap_create_yap_string(inter,
                                                      MEM_strdup("false"));
            }
        } else if (right_val.type == YAP_STRING_VALUE) {
            right_str = right_val.u.string_value;
        } else if (right_val.type == YAP_NATIVE_POINTER_VALUE) {
            sprintf(buf, "(%s:%p)",
                    right_val.u.native_pointer.info->name,
                    right_val.u.native_pointer.pointer);
            right_str = yap_create_yap_string(inter, MEM_strdup(buf));
        } else if (right_val.type == YAP_NULL_VALUE) {
            right_str = yap_create_yap_string(inter, MEM_strdup("null"));
        } 
        result.type = YAP_STRING_VALUE;
        result.u.string_value = chain_string(inter,
                                             left_val.u.string_value,
                                             right_str);
    } else if (left_val.type == YAP_STRING_VALUE
               && right_val.type == YAP_STRING_VALUE) {
        result.type = YAP_BOOLEAN_VALUE;
        result.u.boolean_value
            = eval_compare_string(operator, &left_val, &right_val,
                                  left->line_number);
    } else if (left_val.type == YAP_NULL_VALUE
               || right_val.type == YAP_NULL_VALUE) {
        result.type = YAP_BOOLEAN_VALUE;
        result.u.boolean_value
            = eval_binary_null(inter, operator, &left_val, &right_val,
                               left->line_number);
    } else {
        char *op_str = yap_get_operator_string(operator);
        yap_runtime_error("");
    }

    return result;
}

static YAP_Value eval_logical_and_or_expression(YAP_Interpreter *inter, LocalEnvironment *env, ExpressionType operator, Expression *left, Expression *right)
{
    YAP_Value left_val;
    YAP_Value right_val;
    YAP_Value result;

    result.type = YAP_BOOLEAN_VALUE;
    left_val = eval_expression(inter, env, left);

    if (left_val.type != YAP_BOOLEAN_VALUE) {
        crb_runtime_error(left->line_number, NOT_BOOLEAN_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    if (operator == LOGICAL_AND_EXPRESSION) {
        if (!left_val.i.boolean_value) {
            result.u.boolean_value = YAP_FALSE;
            return result;
        }
    } else if (operator == LOGICAL_OR_EXPRESSION) {
        if (left_val.i.boolean_value) {
            result.u.boolean_value = YAP_TRUE;
            return result;
        }
    } else {
        DBG_panic(("bad operator..%d\n", operator));
    }

    right_val = eval_expression(inter, env, right);
    if (right_val.type != YAP_BOOLEAN_VALUE) {
        crb_runtime_error(right->line_number, NOT_BOOLEAN_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    result.u.boolean_value = right_val.u.boolean_value;

    return result;
}

YAP_Value yap_eval_minus_expression(YAP_Interpreter *inter, LocalEnvironment *env, Expression *operand)
{
    YAP_Value operand_val;
    YAP_Value result;

    operand_val = eval_expression(inter, env, operand);
    if (operand_val.type == YAP_INT_VALUE) {
        result.type = YAP_INT_VALUE;
        result.u.int_value = -operand_val.i.int_value;
    } else if (operand_val.type == YAP_DOUBLE_VALUE) {
        result.type = YAP_DOUBLE_VALUE;
        result.u.double_value = -operand_val.u.double_value;
    } else {
        crb_runtime_error(operand->line_number, MINUS_OPERAND_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }

    return result;
}

static YAP_Value call_yap_function(YAP_Interpreter *inter, LocalEnvironment *env, Expression *expr, FunctionDefinition *func)
{
    YAP_Value value;
    StatementResult result;
    ArgumentList *arg_p;
    ParameterList *param_p;
    LocalEnvironment *local_env;

    local_env = alloc_local_environment();

    for (arg_p = expr->u.function_call_expression.argument, param_p = func->u.yap_f.parameter; arg_p; arg_p = arg_p->next, param_p = param_p->next) {
        YAP_Value arg_val;
        if (param_p == NULL) {
            crb_runtime_error(expr->line_number, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
        }
        arg_val = eval_expression(inter, env, arg_p->expression);
        yap_add_local_variable(local_env, param_p->name, &arg_val);
    }
    if (param_p) {
        crb_runtime_error(expr->line_number, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
    }
    result = yap_execute_statement_list(inter, local_env, func->i.yap_f.block->statement_list);

    if (result.type == RETURN_STATEMENT_RESULT) {
        value = result.u.return_value;
    } else {
        value.type = YAP_NULL_VALUE;
    }
    dispose_local_environment(inter, local_env);

    return value;
}

static YAP_Value eval_function_call_expression(YAP_Interpreter *inter, LocalEnvironment *env, Expression *expr)
{
    YAP_Value value;
    FunctionDefinition *func;

    char *identifier = expr->u.function_call_expression.identifier;

    func = yap_search_function(identifier);
    if (func == NULL) {

    }
    switch (func->type) {
    case YAP_FUNCTION_DEFINITION:
        value = call_yap_function(inter, env, expr, func);
        break;
    case NATIVE_FUNCTION_DEFINITION:
        value = call_native_function(inter, env, expr, func->u.native_f.proc);
        break;
    default:
        DBG_panic(("bad case..%d\n", func->type));
    }

    return value;
}

static YAP_Value call_native_function(YPA_Interpreter *inter, LocalEnvironment *env, Expression *expr, YAP_NativeFunctionProc *proc)
{
    YAP_Value value;
    int arg_count;
    ArgumentList *arg_p;
    YAP_Value *args;
    int i;

    for (arg_count = 0, arg_p = expr->u.function_call_expression.argument; arg_p; arg_p = arg_p = arg_p->next) {
        arg_count++;
    }

    args = MEM_malloc(sizeof(YAP_Value) *arg_count);

    for (arg_p = expr->u.function_call_expression.argument, i = 0; arg_p; arg_p = arg_p->next, i++) {
        args[i] = eval_expression(inter, env, arg_p->expression);
    }
    value = proc(inter, arg_count, args);
    for (i = 0; i < arg_count; i++) {
        release_if_string(&args[i]);
    }
    MEM_free(args);

    return value;
}

static YAP_Value eval_null_expression(void)
{
    YAP_Value v;

    v.type = YAP_NULL_VALUE;

    return v;
}

YAP_Value eval_expression(YAP_Interpreter *inter, LocalEnvironment env, Expression *expr)
{
    YAP_Value v;
    switch (expr->type) {
    case BOOLEAN_EXPRESSION:
        v = eval_boolean_expression(expr->u.boolean_value);
        break;
    case INT_EXPRESSION:
        v = eval_int_expression(expr->u.int_value);
        break;
    case DOUBLE_EXPRESSION:
        v = eval_double_expression(expr->u.double_value);
        break;
    case STRING_EXPRESSION:
        v = eval_string_expression(expr->u.string_value);
        break;
    case IDENTIFIER_EXPRESSION:
        v = eval_identifier_expression(inter, env, expr);
        break;
    case ASSIGN_EXPRESSION:
        v = eval_assign_expression(inter, env, expr->u.assign_expression.variable, expr->u.assign_expression.operand);
        break;
    case ADD_EXPRESSION:
    case SUB_EXPRESSION:
    case MUL_EXPRESSION:
    case DIV_EXPRESSION:
    case MOD_EXPRESSION:
    case EQ_EXPRESSION:
    case NE_EXPRESSION:
    case GT_EXPRESSION:
    case GE_EXPRESSION:
    case LT_EXPRESSION:
    case LE_EXPRESSION:
        v = yap_eval_binary_expression(inter, env, expr->type, expr->u.binary_expression.left, expr->u.bianry_expression.right);
        break;
    case LOGICAL_AND_EXPRESSION:
    case LOGICAL_OR_EXPRESSION:
        v = eval_logical_and_or_expression(inter, env, expr->type, expr->u.binary_expression.left, expr->u.bianry_expression.right);
        break;
    case MINUS_EXPRESSION:
        v = yap_eval_minus_expression(inter, env, expr->u.minus_expression);
        break;
    case FUNCTION_CALL_EXPRESSION:
        v = eval_function_call_expression(inter, env, expr);
        break;
    case NULL_EXPRESSION:
        v = eval_null_expression();
        break;
    case EXPRESSION_TYPE_COUNT_PLUS_1:
    default:
        fprintf(stderr, "不能匹配到表达式类型:%d", expr->type);
    }

    return v;
}

YAP_Value yap_eval_expression(YAP_Interpreter *inter, LocalEnvironment *env, Expression *expr)
{
    return eval_expression(inter, env, expr);
}