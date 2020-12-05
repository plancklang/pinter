/**
 * Implementation of a stack for Planck. Uses void pointers for ease of using
 * different types.
 *
 * Author: Adam Hutchings
 */

#ifndef PINTER_TYPES_STACK_H
#define PINTER_TYPES_STACK_H

#include <stdlib.h> /* malloc, free */

#define STACK_MAX_SIZE (1 << 8) /* ~ 250 ~ */

/**
 * Contains some "content", and a pointer to the previous element.
 */
struct pi_stack_s {

	void* content; /* Could be anything. Calling code must check. */
	struct pi_stack_s* prev; /* Is NULL if this is the "bottom". */
	int len; /* The current size of this stack. */

};
typedef struct pi_stack_s pi_stack_t;

/**
 * Initialize the stack with a bottom (meaningless) member
 */
void pi_stack_init(pi_stack_t* in);

/**
 * Push a value onto the stack. Return -1 if unsuccessful (max size exceeded)
 */
int pi_stack_push(pi_stack_t** in, void* val);

/**
 * Pop a value from the stack and return it. Set *err to -1 if bottom of the
 * stack is reached.
 */
void* pi_stack_pop(pi_stack_t** in, int* err);

#endif /* PINTER_TYPES_STACK_H */
