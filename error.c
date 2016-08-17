#include <stdio.h>
#include <stdarg.h>

void yap_compile_error(char *msg)
{
	line_number = yap_get_current_interpreter()->current_line_number;
	fprintf(stderr, "[%s]:%s,在%3d行\n", "编译期错误", line_number, *msg);
	exit(1);
}

void yap_runtime_error(int line_number, char *msg)
{
	fprintf(stderr, "[%s]:%s,在%3d行\n", "运行期错误", line_number, *msg);
	exit(1);
}