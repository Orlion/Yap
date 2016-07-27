%{
#include <stdio.h>
#include "y.tab.h"

int yywrap(void)
{
	return 1;
}
%}
%start COMMENT STRING_LITERAL_STATE
%%
<INITIAL>"function"     return FUNCTION;
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>"elseif"       return ELSEIF;
<INITIAL>"while"        return WHILE;
<INITIAL>"for"          return FOR;
<INITIAL>"return"       return RETURN_T;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"null"         return NULL_T;
<INITIAL>"true"         return TRUE_T;
<INITIAL>"false"        return FALSE_T;
<INITIAL>"global"       return GLOBAL_T;
<INITIAL>"("            return LP;
<INITIAL>")"            return RP;
<INITIAL>"{"            return LC;
<INITIAL>"}"            return RC;
<INITIAL>";"            return SEMICOLON;
<INITIAL>","            return COMMA;
<INITIAL>"&&"           return LOGICAL_AND;
<INITIAL>"||"           return LOGICAL_OR;
<INITIAL>"="            return ASSIGN;
<INITIAL>"=="           return EQ;
<INITIAL>"!="           return NE;
<INITIAL>">"            return GT;
<INITIAL>">="           return GE;
<INITIAL>"<"            return LT;
<INITIAL>"<="           return LE;
<INITIAL>"+"            return ADD;
<INITIAL>"-"            return SUB;
<INITIAL>"*"            return MUL;
<INITIAL>"/"            return DIV;
<INITIAL>"%"            return MOD;
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    printf("变量:%s", yytext);
}
<INITIAL>([1-9][0-9]*)|"0" {
    printf("整数:%s", yytext);
}
<INITIAL>[0-9]+\.[0-9]+ {
    printf("小数:%s", yytext);
}
<INITIAL>\" {
    printf("字符串开始");
}
<INITIAL>[ \t] ;
<INITIAL>\n {printf("换行");}
<INITIAL>#     BEGIN COMMENT;
<INITIAL>.      {
    char buf[10];

    if (isprint(yytext[0])) {
        buf[0] = yytext[0];
        buf[1] = '\0';
    } else {
        sprintf(buf, "0x%02x", (unsigned char)yytext[0]);
    }

    printf("词法分析错误");
}
<COMMENT>\n     {
    printf("注释结束");
    BEGIN INITIAL;
}
<COMMENT>.      ;
<STRING_LITERAL_STATE>\"        {
    printf("字符串结束");
    BEGIN INITIAL;
}
<STRING_LITERAL_STATE>\n        {
    printf("字符串换行");
}
<STRING_LITERAL_STATE>\\\"      printf("字符串有冒号");
<STRING_LITERAL_STATE>\\n       printf("字符串有换行");
<STRING_LITERAL_STATE>\\t       printf("字符串有制表");
<STRING_LITERAL_STATE>\\\\      printf("字符串有反斜杠");
<STRING_LITERAL_STATE>.         printf("字符串中有%c", yytext[0]);
%%