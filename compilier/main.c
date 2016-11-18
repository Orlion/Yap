#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "DKC.h"
#include "DVM.h"

int main(int argc, char **argv)
{
	FILE *fp;
	DKC_Compiler *compiler;
	DVM_Executable *exe;
	DVM_VirtualMachine *dvm;

	if (argc < 2) {
		fprintf(stderr, "Programe:%s filename arg1, arg2, ...\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "File:%s not found!\n", argv[1]);
		exit(1);
	}

	/* set locale */
	setlocale(LC_CTYPE, "");
	compiler = DKC_create_compiler();
	exe = DKC_compile(compiler, fp);
	dvm = DVM_create_virtual_machine();
	DVM_add_executable(dvm, exe);
	DVM_execute(dvm);

	return 0;
}
