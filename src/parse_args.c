#include "parse_args.h"

pinter_args_t pi_parse(int argc, char** argv) {

	pinter_args_t ret;

	/* At this point, there is only one argument. */
	if (argc > 1) {
		PINTER_ERROR("unexpected argument %s\n", argv[1]);
	} else if (argc == 0) {
		PINTER_ERROR("expected argument (file input)\n");
	}

	if (STREQ(argv[0], "--help", 6)) {
		ret.help = true;
		ret.info = false;
		ret.file = NULL;
	} else if (STREQ(argv[0], "-v", 2)) {
		ret.help = false;
		ret.info = true;
		ret.file = NULL;
	} else {
		ret.help = false;
		ret.info = false;
		ret.file = argv[0];
	}

	return ret;

}
