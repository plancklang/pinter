#include "stack.h"

void pi_stack_init(pi_stack_t* in) {

	in = malloc( sizeof(pi_stack_t) );

	in->content = NULL;
	in->prev = NULL;
	in->len = 1;

}

int pi_stack_push(pi_stack_t** in, void* val) {

	pi_stack_t* new_stack; /* new stack member */
	new_stack->content = val;
	new_stack->prev = *in;

	/* Check length */
	if ((*in)->len >= STACK_MAX_SIZE) {
		return -1;
	}

	new_stack->len = (*in)->len + 1;

	(*in) = new_stack;

	return 0;

}

void* pi_stack_pop(pi_stack_t** in, int* err) {

	if ((*in)->len == 0) {
		*err = -1;
		return NULL;
	}

	void* ret = (*in)->content;

	/* Copy for freeing up */
	pi_stack_t* to_free = *in;

	*in = (*in)->prev;

	free(to_free);

	return ret;

}
