#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "DKC.h"

int main(int argc, char **argv)
{
	FILE *fp;
	DKC_Compilier *compilier;
	DVM_Executeable *exe;
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
	compilier = DKC_create_compilier();
	exe = DKC_compile(compilier, fp);
}