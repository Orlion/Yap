#include "MEM.h"
#include "yaplang.h"

static void add_native_functions(YAP_Interpreter *inter)
{
	YAP_add_native_function(inter, "print", crb_nv_print_proc);
}

YAP_Interpreter *YAP_create_interpreter(void)
{
    MEM_Storage storage;
    YAP_Interpreter *interpreter;

    storage = MEM_open_storage(0);
    interpreter = MEM_storage_malloc(storage, sizeof(YAP_Interpreter_tag));
    interpreter->interpreter_storage = storage;
    interpreter->execute_storage = NULL;
    interpreter->variable = NULL;
    interpreter->function_list = NULL;
    interpreter->statement_list = NULL;
    interpreter->current_line_number = 1;

    yap_set_current_interpreter(interpreter);
    add_native_functions(interpreter);

    return interpreter;
}

void CRB_compile(YAP_Interpreter *interpreter, FILE *fp)
{
    extern int yyparse(void);
    extern FILE *yyin;

    crb_set_current_interpreter(interpreter);

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "[ERROR]\n");
        exit(1);
    }

    crb_reset_string_literal_buffer();
}

void YAP_interpret(YAP_Interpreter *interpreter)
{
    interpreter->execute_storage = MEM_open_storage(0);
    crb_add_std_fp(interpreter);
    crb_execute_statement_list(interpreter, NULL, interpreter->statement_list);
}

void
CRB_dispose_interpreter(YAP_Interpreter *interpreter)
{
    release_global_strings(interpreter);

    if (interpreter->execute_storage) {
        MEM_dispose_storage(interpreter->execute_storage);
    }

    MEM_dispose_storage(interpreter->interpreter_storage);
}

void YAP_dispose_interpreter(YAP_Interpreter *interpreter)
{
    release_global_strings(interpreter);

    if (interpreter->execute_storage) {
        MEM_dispose_storage(interpreter->execute_storage);
    }

    MEM_dispose_storage(interpreter->interpreter_storage);
}

void YAP_add_native_function(YAP_Interpreter *interpreter, char *name, YAP_NativeFunctionProc *proc)
{
	FunctionDefinition *fd;
	fd->name = name;
	fd->type = NATIVE_FUNCTION_DEFINITION;
	fd->u.native_f.proc = proc;
	fd->next = interpreter->function_list;

	interpreter->function_list = fd;
}
