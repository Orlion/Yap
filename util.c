#include <stdio.h>
#include <string.h>
#include "yaplang.h"
#include "MEM.h"

static YAP_Interpreter *st_current_interpreter;

YAP_Interpreter *yap_get_current_interpreter(void)
{
    return st_current_interpreter;
}

void yap_set_current_interpreter(YAP_Interpreter *inter)
{
    st_current_interpreter = inter;
}

void *yap_malloc(size_t size)
{
    void *p;
    YAP_Interpreter *inter;

    inter = yap_get_current_interpreter();
    p = MEM_storage_malloc(inter->interpreter_storage, size);

    return p;
}

FunctionDefinition *yap_search_function(char *name)
{
	FunctionDefinition *pos;
	YAP_Interpreter *inter;

	inter = yap_get_current_interpreter();
	for (pos = inter->function_list; pos; pos = pos->next) {
		if (!strcmp(pos->name, name))
			break;
	}

	return pos;
}

void *yap_execute_malloc(YAP_Interpreter *inter, size_t size)
{
	void *p;

	p = MEM_storage_malloc(inter->execute_storage, size);

	return p;
}

void YAP_add_global_variable(YAP_Interpreter *inter, char *identifier, YAP_Value *value)
{
	Variable 	*new_variable;

	new_variable = yap_execute_malloc(inter, sizeof(Variable));
	new_variable->name = yap_execute_malloc(inter, strlen(identifier) + 1);
	strcpy(new_variable->name, identifier);
	new_variable->next = inter->variable;
	inter->variable = new_variable;
	new_variable->value = *value;
}

void yap_add_global_variable(LocalEnvironment *env, char *identifier, YAP_Value *value)
{
	Variable *new_variable;

	new_variable = MEM_malloc(sizeof(Variable));
	new_variable->name = identifier;
	new_variable->value = *value;
	new_variable->next = env->variable;
	env->variable = new_variable;
}

Variable *yap_search_local_variable(LocalEnvironment *env, char *identifier)
{
	Variable *pos;

	if (env == NULL)
		return NULL;
	for (pos = env->variable; pos; pos = pos->next) {
		if (!strcmp(pos->name, identifier))
			break;
	}

	if (pos == NULL) {
		return NULL;
	} else {
		return pos;
	}
}

void yap_add_local_variable(LocalEnvironment *env, char *identifier, YAP_Value *value)
{
	Variable *new_variable;

	new_variable = MEM_malloc(sizeof(Variable));
	new_variable->name = identifier;
	new_variable->value = *value;
	new_variable->next = env->variable;
	env->variable = new_variable;
}

char *yap_get_operator_string(ExpressionType type)
{
    char        *str;
    char msg[100];

    switch (type) {
    case BOOLEAN_EXPRESSION:    /* FALLTHRU */
    case INT_EXPRESSION:        /* FALLTHRU */
    case DOUBLE_EXPRESSION:     /* FALLTHRU */
    case STRING_EXPRESSION:     /* FALLTHRU */
    case IDENTIFIER_EXPRESSION:
    	sprintf(msg, "不存在ExpressionType-%d", type);
        yap_bug_error(msg);
        break;
    case ASSIGN_EXPRESSION:
        str = "=";
        break;
    case ADD_EXPRESSION:
        str = "+";
        break;
    case SUB_EXPRESSION:
        str = "-";
        break;
    case MUL_EXPRESSION:
        str = "*";
        break;
    case DIV_EXPRESSION:
        str = "/";
        break;
    case MOD_EXPRESSION:
        str = "%";
        break;
    case LOGICAL_AND_EXPRESSION:
        str = "&&";
        break;
    case LOGICAL_OR_EXPRESSION:
        str = "||";
        break;
    case EQ_EXPRESSION:
        str = "==";
        break;
    case NE_EXPRESSION:
        str = "!=";
        break;
    case GT_EXPRESSION:
        str = "<";
        break;
    case GE_EXPRESSION:
        str = "<=";
        break;
    case LT_EXPRESSION:
        str = ">";
        break;
    case LE_EXPRESSION:
        str = ">=";
        break;
    case MINUS_EXPRESSION:
        str = "-";
        break;
    case FUNCTION_CALL_EXPRESSION:  /* FALLTHRU */
    case NULL_EXPRESSION:  /* FALLTHRU */
    case EXPRESSION_TYPE_COUNT_PLUS_1:
    default:
        sprintf(msg, "不存在ExpressionType-%d", type);
        yap_bug_error(msg);
    }

    return str;
}

Variable *yap_search_global_variable(YAP_Interpreter *inter, char *identifier)
{
    Variable    *pos;

    for (pos = inter->variable; pos; pos = pos->next) {
        if (!strcmp(pos->name, identifier))
            return pos;
    }

    return NULL;
}

