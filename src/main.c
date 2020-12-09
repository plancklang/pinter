/**
 * This is the file containing the main function for pinter.
 * 
 * Adam Hutchings (adam.abahot@gmail.com)
 */

#include <stdio.h> /* FILE, fopem */

#include <src/behavior.h> /* execute_bytecode */
#include <src/decode.h> /* decode */
#include <src/parse_args.h> /* pi_parse, pinter_args_t */
#include <src/util.h> /* PINTER_ERROR, PL_SUCCESS */
#include <src/vm.h> /* pi_vm_t, etc. */

#define VM_SIZE_DEFAULT (1 << 18) /* Like 260 KB or so */

void usage() {
	printf("\
Usage:\n\
	--help see this message\n\
	-v see the version\n\
	[file]: execute [file]\n\
");
}

void info() {
	printf("Pinter %s\n", VERSION);
}


int main(int argc, char** argv) {

	--argc, ++argv; /* "pinter" itself doesn't need to be parsed */
	pinter_args_t args = pi_parse(argc, argv);

	if (args.help) {
		usage();
	} else if (args.info) {
		info();	
	} else {
		
		/* Open the file */

		FILE* pi_read = fopen(args.file, "r");

		if (pi_read == NULL) {
			PINTER_ERROR("could not open file:\n\t%s\n", args.file);
		}

		int main_error = 0; /* Error status */

		pi_vm_t vm;
		init_vm(&vm, VM_SIZE_DEFAULT, &main_error);

		if (main_error) {
			switch (main_error) {
				case VM_ERR_INVALID_SIZE:
					PINTER_ERROR("internal error: invalid size for vm: %d\n", VM_SIZE_DEFAULT);
				case VM_ERR_INVALID_ALLOC:
					PINTER_ERROR("internal error: invalid malloc() call for vm\n");
				default: /* Nothing */;
			}
		}

		/* Parse bytecodes */
		int byt_ct;
		vm.bytecodes = decode(pi_read, &byt_ct, &main_error);
		vm.bytecode_ct = byt_ct;

		/* Check for errors in bytecodes */
		if (main_error) {
			switch (main_error) {
				case ERR_NULL_FILE:
					PINTER_ERROR("internal error: file invalidated during execution\n");
				case ERR_PARTIAL_INSTRUCTION:
					PINTER_ERROR("invalid file length (not divisible by 9)\n");
				case ERR_INVALID_OPCODE:
					PINTER_ERROR("invalid opcode in file\n");
			}
		}

		/* Let's execute the bytecodes! */
		while ( !execute_bytecode(&vm) );

		/* Everything went okay (error handling here later, perhaps) */

	}

	return PL_SUCCESS;

}
