#include "yaplang.h"

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
