#include <stdio.h>
#include <stdarg.h>

void yap_compile_error(char *msg)
{
	line_number = yap_get_current_interpreter()->current_line_number;
	fprintf(stderr, "[编译期错误]:%s,在%3d行\n", line_number, *msg);
	exit(1);
}

void yap_runtime_error(int line_number, char *msg)
{
	fprintf(stderr, "[运行期错误]:%s,在%3d行\n", line_number, *msg);
	exit(1);
}

void yap_bug_error(char *msg)
{
	fprintf(stderr, "[Yap Bug]:%s\n", , *msg);
	exit(1);
}