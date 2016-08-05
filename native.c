#include <stdio.h>
#include "YAP_dev.h"
#include "yaplang.h"

#define NATIVE_LIB_NAME "yap.lang.file"

static YAP_NativePointerInfo st_native_lib_info = {
    NATIVE_LIB_NAME
};

YAP_Value yap_nv_print_proc(YAP_Interpreter *interpreter, int arg_count, YAP_Value *args)
{
    YAP_Value value;
    value.type = YAP_NULL_VALUE;

    if (arg_count < 1) {
        fprintf(stderr, "参数少\n");
    } else if (arg_count > 1) {
        fprintf(stderr, "参数多\n");
    }
    switch (args[0].type) {
    case YAP_BOOLEAN_VALUE:
        if (args[0].u.boolean_value) {
            printf("true");
        } else {
            printf("false");
        }
        break;
    case YAP_INT_VALUE:
        printf("%d", args[0].u.int_value);
        break;
    case YAP_DOUBLE_VALUE:
        printf("%f", args[0].u.double_value);
        break;
    case YAP_STRING_VALUE:
        printf("%s", args[0].u.string_value->string);
        break;
    case YAP_NATIVE_POINTER_VALUE:
        printf("(%s:%p)", args[0].u.native_pointer.info->name, args[0].u.native_pointer.pointer);
        break;
    case YAP_NULL_VALUE:
        printf("null");
        break;
    }

    return value;
}

void yap_add_std_fp(YAP_Interpreter *inter)
{
    YAP_Value fp_value;

    fp_value.type = YAP_NATIVE_POINTER_VALUE;
    fp_value.u.native_pointer.info = &st_native_lib_info;

    fp_value.u.native_pointer.pointer = stdin;
    YAP_add_global_variable(inter, "STDID", &fp_value);

    fp_value.u.native_pointer.pointer = stdout;
    YAP_add_global_variable(inter, "STDOUT", &fp_value);

    fp_value.u.native_pointer.pointer = stderr;
    YAP_add_global_variable(inter, "STDERR", &fp_value);
}
