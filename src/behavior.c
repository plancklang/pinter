#include "behavior.h"

int execute_bytecode(pi_vm_t* vm) {

	bytecode_t b = vm->bytecodes[vm->bytecode_exec];

	/* Casts for internal use */
	signed char* leftc = (signed char*) &(vm->cells[b.left]);
	int32_t* lefti = (int32_t*) &(vm->cells[b.left]);
	int64_t* leftd = (int64_t*) &(vm->cells[b.left]);

	switch (b.opcode) {
		case NXLL:
			break;
		case SETV:
			*leftc = (signed char) vm->cells[b.right];
			break;
		case SETC:
			*leftc = (signed char) vm->cells[b.right];
			break;
		case CADD:
			*leftc += (signed char) vm->cells[b.right];
			break;
		case CSUB:
			*leftc -= (signed char) vm->cells[b.right];
			break;
		case CMUL:
			*leftc *= (signed char) vm->cells[b.right];
			break;
		case CDIV:
			*leftc /= (signed char) vm->cells[b.right];
			break;
		case IADD:
			*lefti += (int32_t) vm->cells[b.right];
			break;
		case ISUB:
			*lefti -= (int32_t) vm->cells[b.right];
			break;
		case IMUL:
			*lefti *= (int32_t) vm->cells[b.right];
			break;
		case IDIV:
			*lefti /= (int32_t) vm->cells[b.right];
			break;
		case DADD:
			*leftd += (int64_t) vm->cells[b.right];
			break;
		case DSUB:
			*leftd -= (int64_t) vm->cells[b.right];
			break;
		case DMUL:
			*leftd *= (int64_t) vm->cells[b.right];
			break;
		case DDIV:
			*leftd /= (int64_t) vm->cells[b.right];
			break;
		case CALL:
			vm_call(vm, b.right, b.left);
			break;
		case RTRN:
			vm_ret(vm, b.left, b.right);
			break;
		case EXIT:
			/* Go to the end */
			vm->bytecode_exec = vm->bytecode_ct - 1;
			break;
		case DREF:
			
			*( (int32_t*) &(vm->cells[b.right]) ) = (int32_t) vm->cells[
				(int32_t) vm->cells[b.left]
			];
			break;
		default:
			return PI_INVALID_CODE;
	}

	/* Go to the next bytecode if there is one */
	(vm->bytecode_exec)++;
	if (vm->bytecode_exec < vm->bytecode_ct)
		return 0;
	else
		return PI_EXECUTION_DONE;

}
