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

	vm->stack_size = VM_MAX_ARGS_CT;

	pi_stack_init(&(vm->call_stack));

	vm->bytecode_exec = 0;

	/* TODO initialize bytecodes */
	
	*err = 0; /* Nothing went wrong. */

}

int vm_stalloc(pi_vm_t* vm, int amount, int* err) {

	/* Check free size */
	if (vm->cell_ct - vm->stack_size > amount) {
		*err = -1;
		return -1;
	}

	/* Move the stack pointer forward and return the address. */
	vm->stack_size += amount;

	*err = 0;
	return vm->stack_size - amount;

}

int vm_call(pi_vm_t* vm, int jump, int ret_dest) {

	pi_stack_t* st = &vm->call_stack;

	call_t push = {
		.instruction_ret = vm->bytecode_exec,
		.stack_loc = vm->stack_size,
		.ret_loc = ret_dest
	};

	/* Save the current call stack location */
	if (pi_stack_push(&st, &push) == -1) {
		return -1; /* An error occurred. */
	}

	vm->bytecode_exec = jump;

	return 0; /* Success */

}

int vm_ret(pi_vm_t* vm, int ret_src, int size) {

	int err;

	pi_stack_t* st = &vm->call_stack;

	call_t* top_call = (call_t*) pi_stack_pop(&st, &err);

	if (err == -1) {
		return -1;
	}

	vm->stack_size = top_call->stack_loc; /* Move the stack pointer back */

	/* Copy return value out */
	memcpy(
		&vm->cells[top_call->ret_loc],
		&vm->cells[ret_src],
		size
	);

	return 0;

}
