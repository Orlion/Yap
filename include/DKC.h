#ifndef PUBLIC_DKC_H_INCLUDE
#define PUBLIC_DKC_H_INCLUDE
#include <stdio.h>

typedef struct DKC_Compiler_tag DKC_Compiler;

typedef enum {
	DKC_FILE_INPUT_MODE = 1,
	DKC_STRING_INPUT_MODE
} DKC_InputMode;

DKC_Compiler *DKC_create_compiler(void);
#endif