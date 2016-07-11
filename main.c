#include <stdio.h>

int main(int argv, char **argv)
{
	YAP_Interpreter *interpreter;
	FILE *fp;

	if (argv != 2) {
		fprintf(stderr, "请输入文件名\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "文件:%s不存在\n", argv[1]);
		exit(1);
	}

	yyin = fp;
	if (yyparse()) {
		fprintf(stderr, "Error\n");
		exit(1);
	}

	return 0;	
}
