/**
 * A type for the VM that Planck bytecodes run on during interpretation.
 *
 * Author: Adam Hutchings
 */

#ifndef PINTER_VM_H
#define PINTER_VM_H

#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy, memset */

#include <src/types/bytecodes.h> /* bytecode_t */
#include <src/types/stack.h> /* pi_stack_t */

#define VM_SIZE_MIN 1 << 16 /* ~ 65 KB */
#define VM_SIZE_MAX 1 << 31 /* ~ 2  GB */

#define VM_ERR_INVALID_SIZE -1 /* If the size is outside the bounds above */
#define VM_ERR_INVALID_ALLOC -2 /* If malloc fails for whatever reason */

#define VM_MAX_ARGS_CT 16

/**
 * A given member of the call stack. Contains the instruction to jump back to
 * once the function returns, and the location for the stack to rewind to.
 */
typedef struct {

	int instruction_ret;
	int stack_loc;

} call_t;

typedef char vm_cell_t; /* each cell is 8 bits */

typedef struct {

	vm_cell_t* cells;
	int cell_ct;

	bytecode_t* bytecodes;
	int bytecode_ct;

	int bytecode_exec; /* The bytecode currently executing */

	int stack_size; /* The location of the stack pointer */

	pi_stack_t /* call_t */ call_stack;

} pi_vm_t;

/**
 * Initializes the given vm pointer with [size] cells, and sets *err if
 * something goes wrong.
 */
void init_vm(pi_vm_t* vm, int size, int* err);

/**
 * Allocates a given amount of memory from the VM, and moves the stack pointer
 * to match. If something goes wrong (not enough free memory), *err is set to
 * -1 and the function returns.
 */
int vm_stalloc(pi_vm_t* vm, int amount, int* err);

/**
 * Saves the current location of the stack pointer, and the current instruction,
 * then jumps to the location given by jump. Arguments need to be pushed onto the
 * stack before this. ret_val is where the return value should go.
 */
void vm_call(pi_vm_t* vm, int jump, int ret_val);

/**
 * Pops a stack frame and returns a value. The value to be returned is in cell
 * ret_src, and should return to cell ret_dest , with size bytes being copied
 * over.
 */
void vm_ret(pi_vm_t* vm, int ret_dest, int ret_src, int size)

#endif /* PINTER_VM_H */
