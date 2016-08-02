#ifndef PUBLIC_YAP_DEV_H_INCLUDED
#define PUBLIC_YAP_DEV_H_INCLUDED
#include "YAP.h"

typedef enum {
    YAP_FALSE = 0,
    YAP_TRUE = 1
} YAP_Boolean;

typedef struct {
	char	*name;
} YAP_NativePointerInfo;

typedef struct YAP_String_tag YAP_String;

typedef struct {
	YAP_NativePointerInfo	*info;		/* 信息 */
	void					*pointer;	/* 值 */
} YAP_NativePointer;

typedef enum {
	YAP_BOOLEAN_VALUE = 1,		/* 布尔型 */
	YAP_INT_VALUE,				/* 整型 */
	YAP_DOUBLE_VALUE,			/* 实数型 */
	YAP_STRING_VALUE,			/* 字符串 */
	YAP_NATIVE_POINTER_VALUE,	/* 原生指针型，类似于php中资源类型（file...） */
	YAP_NULL_VALUE				/* null */
} YAP_ValueType;

typedef struct {
    YAP_ValueType       		type;
    union {
        YAP_Boolean     		boolean_value;
        int             		int_value;
        double          		double_value;
        YAP_String      		*string_value;
        YAP_NativePointer       native_pointer;
    } u;
} YAP_Value;

typedef YAP_Value YAP_NativeFunctionProc(YAP_Interpreter *interpreter, int arg_count, YAP_Value *args);

void YAP_add_native_function(YAP_Interpreter *interpreter, char *name, YAP_NativeFunctionProc *proc);

#endif