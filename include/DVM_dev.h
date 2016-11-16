#ifndef DVM_DEV_H_INCLUDE
#define DVM_DEV_H_INCLUDE
#include "DVM.h"

typedef DVM_Value DVM_NativeFunctionProc(DVM_VirtualMachine *dvm, int arg_count, DVM_Value *args);

#endif /* DVM_DEV_H_INCLUDE */