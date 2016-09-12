#ifndef PUBLIC_DVM_CODE_H_INCLUDED
#define PUBLIC_DVM_CODE_H_INCLUDED

#include "DVM.h"

typedef struct DVM_TypeSpecifier_tag DVM_TypeSpecifier;

typedef struct {
	char *name;
	DVM_TypeSpecifier *type;
} DVM_LocalVariable;

typedef enum {
	DVM_BOOLEAN_TYPE,
	DVM_INT_TYPE,
	DVM_DOUBLE_TYPE,
	DVM_STRING_TYPE
} DVM_BasicType;	/* 基本数据类型 */

typedef enum {
	DVM_FUNCTION_DERIVE
} DVM_DeriveTag;

typedef struct {
	int 					parameter_count;
	DVM_LocalVariable 	*parameter;
} DVM_FunctionDerive;

typedef struct DVM_TypeDerive_tag {
	DVM_DeriveTag 	tag;
	union {
		DVM_FunctionDerive 	function_d;
	} u;
} DVM_TypeDerive; /* 派生类型 */

struct DVM_TypeSpecifier_tag {
	DVM_BasicType 	basic_type;
	int 				derive_count;
	DVM_TypeDerive 	*derive;
};

typedef enum {
	DVM_CONSTANT_INT,
	DVM_CONSTANT_DOUBLE,
	DVM_CONSTANT_STRING
} DVM_ConstantPoolTag;

typedef wchar_t DVM_Char;

typedef struct {
	DVM_ConstantPoolTag 	tag;
	union {
		int 			c_int;
		double 		c_double;
		DVM_Char 	*c_string;
	} u;
} DVM_ConstantPool;

typedef struct {
	char 				*name;
	DVM_TypeSpecifier 	*type;
} DVM_Variable;	/* 全局变量 */

typedef unsigned char DVM_Byte;

typedef struct {
	int line_number;	/* 源代码的行号 */
	int start_pc;	/* 字节码的开始位置 */
	int pc_start;	/* 从start_pc开始接下来有几个字节码对应着同一line_number */
} DVM_LineNumber;	/* 运行字节码报错时显然不能报字节码的当前行数而是要报对应的源代码行数，这个结构体保存对应关系 */

typedef struct {
	DVM_TypeSpecifier 	*type;	/* type是返回值的类型 */
	char 				*name;	/* 函数名 */
	int 					parameter_count;
	DVM_LocalVariable 	*parameter;
	/* is_implemented表示这个函数是否在这个DVM_Executable中实现，例如print（）函数原生实现，使用者没有定义所以is_implemented为false */
	DVM_Boolean 			is_implemented;
	int 					local_variable_count;
	DVM_LocalVariable	*local_variable;
	int 					code_size;
	DVM_Byte 			*code;	/* 指向该函数对应的字节码 */
	int 					line_number_size;
	DVM_LineNumber 		*line_number;
	int 					need_stack_size;
} DVM_Function;

struct DVM_Executable_tag {
	int 					constant_pool_count;
	/* 常量池，保存常量的内存空间。比如push_double 2.5时，不是直接把2.5这个数放到字节码中，而是放到constant_pool中，字节码用常量的索引 */
	DVM_ConstantPool 	*constant_pool;
	int					global_variable_count;
	/* 全局变量列表 */
	DVM_Variable 		*global_variable;
	int					function_count;
	DVM_Function			*function;		/* 函数，将函数里要执行语句的字节码保存在里面 */
	int 					code_size;
	DVM_Byte 			*code;		/* 顶层结构的代码，因为Diksam可以在顶层结构中书写代码，此成员用来保存这些代码生成的字节码 */
	int 					line_number_size;
	DVM_LineNumber		*line_number; 		/* 保存字节码和与之对应的源代码的行号 */
	int 					need_stack_size; /* 保存顶层结构的代码对栈的需要量； 每个函数对栈的需要量都保存在各自的DVM_Function中 */
}
#endif