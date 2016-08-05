#include <stdio.h>
#include <stdlib.h>
#include "YAP.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "[ERROR]:请输入文件名\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "[ERROR]:文件:%s不存在\n", argv[1]);
		exit(1);
	}
    /* 创建解释器 */
	YAP_Interpreter *interpreter = YAP_create_interpreter();
	/* 词法分析与语法分析 */
    YAP_compile(interpreter, fp);
    /* 解释 */
    /* YAP_interpret(interpreter); */
    /* dispose解释器 */
    // YAP_dispose_interpreter(interpreter);

	return 0;	
}
