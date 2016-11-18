#ifndef PUBLIC_DVM_H_INCLUDED
#define PUBLIC_DVM_H_INCLUDED

typedef struct DVM_Executable_tag DVM_Executable;
typedef struct DVM_VirtualMachine_tag DVM_VirtualMachine;

typedef enum {
	DVM_FALSE = 0,
	DVM_TRUE = 1
} DVM_Boolean;

DVM_VirtualMachine *DVM_create_virtual_machine(void);
void DVM_add_executable(DVM_VirtualMachine *dvm, DVM_Executable *executable);
DVM_Value DVM_Execute(DVM_VirtualMachine *dvm);
#endif