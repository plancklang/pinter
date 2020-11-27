/**
 * This file contains utilities to parse the command-line arguments given to
 * pinter into one object, which can then be accessed by the rest of these
 * routines and used to modify the code.
 *
 * Author: Adam Hutchings (adam.abahot@gmail.com)
 */

#include <stdbool.h> /* bool, false, true */

#include <src/util.h> /* PINTER_ERROR */

#ifndef PINTER_PARSE_ARGS_H
#define PINTER_PARSE_ARGS_H

typedef struct {

	bool help; /* whether --help was passed as an option */
	char* file; /* which file to read in */
	bool info; /* should pinter show info */

} pinter_args_t;

pinter_args_t pi_parse(int argc, char** argv);

#endif /* PINTER_PARSE_ARGS_H */
