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
	
	*err = 0; /* Nothing went wrong. */

}
