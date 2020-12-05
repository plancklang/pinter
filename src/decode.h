/**
 * This file provides the utility of opening a text file and producing an array
 * of bytecodes for the use of the VM.
 *
 * Author: Adam Hutchings
 */

#include <stdio.h> /* FILE */
#include <stdlib.h> /* malloc */

#include <src/types/bytecodes.h> /* bytecode_t, etc. */

#define ERR_NULL_FILE -1 /* If a file doesn't exist */
#define ERR_PARTIAL_INSTRUCTION -2 /* If the byte count is not a * of 9 */
#define ERR_INVALID_OPCODE -3 /* If the opcode is currently unsupported */

/**
 * Decode the file given by fp and produce an array of bytecodes. Will set *err
 * and return if something unexpectedly goes wrong. Also, ct will be set to the
 * number of bytecodes in the list.
 */
bytecode_t* decode(FILE* fp, int* ct, int* err);
