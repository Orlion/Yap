#include <stdio.h>
#include <stdarg.h>

struct {
	char *string;
} VString;

static void clear_v_string(VString *v)
{
    v->string = NULL;
}

void yap_compile_error(CompileError id, ...)
{
	int     line_number;

	self_check();
	va_start(ap, id);
	line_number = yap_get_current_interpreter()->current_line_number;

	fprintf(stderr, "%3d:%s\n", line_number, "编译错误");

	exit(1);
}
