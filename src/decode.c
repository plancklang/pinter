#include "decode.h"

bytecode_t* decode(FILE* fp, int* ct, int* err) {

	bytecode_t* ret;

	if (fp == NULL) {
		*err = ERR_NULL_FILE;
		return ret;
	}

	/* Get the size of the file */
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	printf("%d\n", size);

	/* Get contents of file (nice) */
	char contents[size - 1];
	for (int i = 0; i < size - 1; contents[i] = getc(fp), i++);

	if ( (size % 9) ) {
		*err = ERR_PARTIAL_INSTRUCTION;
		return ret;
	}

	ret = malloc( (size / 9) * sizeof(bytecode_t) );
	*ct = size / 9;

	for (int i = 0; i < *ct; i++) {

		/* Set every bytecode */

		/* Check if the opcode is allowed */
		if ( ((opcode_t) (contents[ (i * 9) ])) >= BYTECODE_MAX ) {
			*err = ERR_INVALID_OPCODE;
			return ret;
		}

		ret[i].opcode = (opcode_t) (contents[ (i * 9) ]);
		ret[i].left = (operand_t) (contents[ (i * 9) + 1 ]);
		ret[i].right = (operand_t) (contents[ (i * 9) + 5 ]);

	}

	*err = 0;
	return ret;

}
