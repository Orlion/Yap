#include <stdio.h>
#include <stdlib.h>

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

	extern int yyparse(void);
    extern FILE *yyin;
    /* 创建解释器 */
	CRB_Interpreter *interpreter = CRB_create_interpreter();	
	/* 词法分析与语法分析 */
    CRB_compile(interpreter, fp);	
    /* 解释 */
    CRB_interpret(interpreter);		
    /* dispose解释器 */
    CRB_dispose_interpreter(interpreter);	
    /* 打印 */
    MEM_dump_blocks(stdout);	
	yyin = fp;
	if (yyparse()) {
		fprintf(stderr, "[ERROR]\n");
		exit(1);
	}

	return 0;	
}