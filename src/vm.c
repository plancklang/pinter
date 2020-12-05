#include "vm.h"

void init_vm(pi_vm_t* vm, int size, int* err) {

	if ( (size < VM_SIZE_MIN) || (size > VM_SIZE_MAX) ) {
		*err = VM_ERR_INVALID_SIZE;
		return;
	}

	vm->cells = malloc( size * sizeof(vm_cell_t) );
	if (vm->cells == NULL) {
		*err = VM_ERR_INVALID_ALLOC;
		return;
	}
	vm->cell_ct = size;

	/* Set everything to 0 to begin */
	memset(vm->cells, 0, size);

	vm->stack_size = AM_MAX_ARGS_CT;

	pi_stack_init(vm->&call_stack);

	bytecode_exec = 0;

	/* TODO initialize bytecodes */
	
	*err = 0; /* Nothing went wrong. */

}

int vm_stalloc(pi_vm_t* vm, int amount, int* err) {

	/* Check free size */
	if (vm->size - vm->stack_size > amount) {
		*err = -1;
		return -1;
	}

	/* Move the stack pointer forward and return the address. */
	vm->stack_size += amount;

	*err = 0;
	return vm->stack_size - amount;

}

int vm_call(pi_vm_t* vm, int jump, int ret_dest) {

	/* Save the current call stack location */
	if (pi_stack_push(vm->&&call_stack, vm->bytecode_exec) == -1) {
		return -1; /* An error occurred. */
	}

	vm->bytecode_exec = jump;

}

int vm_ret(pi_vm_t* vm, int ret_src, int size) {

	int err;

	call_t* top_call = (call_t*) pi_stack_pop(vm->&&call_stack, &err);

	if (err == -1) {
		return -1;
	}

	vm->stack_size = top_call->stack_loc; /* Move the stack pointer back */

	/* Copy return value out */
	memcpy(
		vm->cells[top_call->instruction_ret]
		vm->cells[ret_src],
		size
	);

	return 0;

}
