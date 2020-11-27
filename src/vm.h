/**
 * A type for the VM that Planck bytecodes run on during interpretation.
 *
 * Author: Adam Hutchings
 */

#ifndef PINTER_VM_H
#define PINTER_VM_H

#include <stdlib.h> /* malloc */
#include <string.h> /* memset */

#define VM_SIZE_MIN 1 << 16 /* ~ 65 KB */
#define VM_SIZE_MAX 1 << 31 /* ~ 2  GB */

#define VM_ERR_INVALID_SIZE -1 /* If the size is outside the bounds above */
#define VM_ERR_INVALID_ALLOC -2 /* If malloc fails for whatever reason */

typedef char vm_cell_t; /* each cell is 8 bits */

typedef struct {

	vm_cell_t* cells;
	int cell_ct;

} pi_vm_t;

/**
 * Initializes the given vm pointer with [size] cells, and sets *err if
 * something goes wrong.
 */
void init_vm(pi_vm_t* vm, int size, int* err);

#endif /* PINTER_VM_H */
