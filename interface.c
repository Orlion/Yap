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

void CRB_compile(CRB_Interpreter *interpreter, FILE *fp)
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