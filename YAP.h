#ifndef PUBLIC_YAP_H_INCLUDED
#define PUBLIC_YAP_H_INCLUDED
#include <stdio.h>

typedef struct YAP_Interpreter_tag YAP_Interpreter;

YAP_Interpreter *YAP_create_interpreter(void);
void YAP_compile(YAP_Interpreter *interpreter, FILE *fp);
void YAP_interpret(YAP_Interpreter *interpreter);
void YAP_dispose_interpreter(YAP_Interpreter *interpreter);

#endif /* PUBLIC_CRB_H_INCLUDED */
