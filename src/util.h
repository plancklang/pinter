/**
 * This file includes utility routines for pinter, such as erroring out
 * or providing debug messages.
 *
 * Author: Adam Hutchings
 */

#include <stdio.h> /* fprintf, stderr */
#include <stdlib.h> /* exit */
#include <string.h> /* strncmp */

#define PL_SUCCESS 0
#define PL_ERROR 1

#define PINTER_ERROR(...) do {                      \
	fprintf(stderr, "Error: pinter: " __VA_ARGS__); \
	exit(PL_ERROR);                                 \
} while (0)

#define PINTER_DEBUG(...) do {                      \
	fprintf(stderr, "Debug: pinter: " __VA_ARGS__); \
} while (0)

#define STREQ(str1, str2, len) !strncmp(str1, str2, len)
