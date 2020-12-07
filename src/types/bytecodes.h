/**
 * This file defines the bytecode type, and related types (such as the opcode
 * type).
 *
 * Author: Adam Hutchings
 */

#ifndef PINTER_TYPES_BYTECODES_H
#define PINTER_TYPES_BYTECODES_H

#include <stdint.h> /* int32_t */

typedef enum {

	NXLL,
	SETC,
	SETV,
	CADD,
	CSUB,
	CMUL,
	CDIV,
	IADD,
	ISUB,
	IMUL,
	IDIV,
	DADD,
	DSUB,
	DMUL,
	DDIV,
	CALL,
	RTRN,
	EXIT,
	DREF,
	BYTECODE_MAX, /* Put this at the end of the list always */

} opcode_t;

typedef int32_t operand_t; /* Each operand is four bytes. */

typedef struct {

	opcode_t opcode;
	operand_t left;
	operand_t right;

} bytecode_t;

#endif /* PINTER_TYPES_BYTECODES_H */
