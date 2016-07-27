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

	yyin = fp;
	if (yyparse()) {
		fprintf(stderr, "[ERROR]\n");
		exit(1);
	}

	return 0;	
}