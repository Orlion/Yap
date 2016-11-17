#include "dvm_pri.h"

DVM_VirtualMachine *DVM_create_virtual_machine(void)
{
	DVM_VirtualMachine *dvm;

	dvm = MEM_malloc(sizeof(DVM_VritualMachine));
	dvm->stack.alloc_size = STACK_ALLOC_SIZE;
	dvm->stack.stack = MEM_malloc(sizeof(DVM_Value) * STACK_ALLOC_SIZE);
	dvm->stack.pointer_flags = MEM_malloc(sizeof(DVM_Value) * STACK_ALLOC_SIZE);
	dvm->stack.stack_pointer = 0;
	dvm->heap.current_heap_size = 0;
	dvm->heap.header = NULL;
	dvm->heap.current_threshold = HEAP_THRESHOLD_SIZE;
	dvm->function = NULL;
	dvm->function_count = 0;
	dvm->executable = NULL;

	dvm_add_native_function(dvm);
	
	return dvm;
}

void DVM_add_native_function(DVM_VirtualMachine *dvm, char *func_name, DVM_NativeFunctionProc *proc, int arg_count)
{
	dvm->function = MEM_realloc(dvm->function, sizeof(Function) * (dvm->function_count + 1));

	dvm->function[dvm->function_count].name = MEM_strdup(func_name);
	dvm->function[dvm->function_count].kind = NATIVE_FUNCTION;
	dvm->function[dvm->function_count].u.native_f.proc = proc;
	dvm->function[dvm->function_count].u,native_f.arg_count = arg_count;
	dvm->function_count++;
}

static void expand_stack(DVM_VirtualMachine *dvm, int need_stack_size)
{
	int revalue_up;
	int ret;

	rest = dvm->stack.alloc_size - dvm->stack.stack_pointer;
	if (rest <= need_stack_size) {
		revalue_up = ((rest / STACK_ALLOC_SIZE) + 1) * STACK_ALLOC_SIZE;

		dvm->stack.alloc_size += revalue_up;
		dvm->stack.stack = MEM_realloc(dvm->stack.stack, dvm->stack.alloc_size * sizeof(DVM_Value));
		dvm->stack.pointer_flags = MEM_realloc(dvm->stack.pointer_flags, dvm->stack.alloc_size * sizeof(DVM_Boolean));
	}
}

static DVM_Value execute(DVM_VirtualMachine *dvm, Function *func, DVM_Byte *code, int code_size)
{
	int pc;
	int base;
	DVM_Value ret;
	DVM_Value *stack;

	stack = dvm->stack.stack;
	exe = dvm->executable;

	for (pc = dvm->pc; pc < code_size; ) {
		/* TODO: execute */
	}
}

DVM_Value DVM_execute(DVM_VirtualMachine *dvm)
{
	DVM_Value ret;

	dvm->pc = 0;
	expand_stack(dvm, dvm->executable->need_stack_size);
	execute(dvm, NULL, dvm->executable->code, dvm->executable->code_size);

	return ret;
}
