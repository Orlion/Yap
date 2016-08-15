#include <stdio.h>
#include <stdarg.h>

void yap_compile_error(CompileError id, ...)
{
	line_number = yap_get_current_interpreter()->current_line_number;
	fprintf(stderr, "%3d:%s\n", line_number, "编译错误");
	exit(1);
}

void yap_runtime_error(char *msg)
{
	line_number = yap_get_current_interpreter()->current_line_number;
	fprintf(stderr, "[%s]:%s,在%3d行\n", "运行错误", line_number, *msg);
	exit(1);
}