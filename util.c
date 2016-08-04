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