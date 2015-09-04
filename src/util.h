#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdlib.h>
#include "types.h"

//#define DEBUG
#define VERSION "0.3"

#define _RED     "\x1b[31m"
#define _GREEN   "\x1b[32m"
#define _YELLOW  "\x1b[33m"
#define _BLUE    "\x1b[34m"
#define _MAGENTA "\x1b[35m"
#define _CYAN    "\x1b[36m"
#define _RESET   "\x1b[0m"

/* Cleaner access to an argument's value */
#define ARGVAL(ARG, TYPE) \
	(ARG)->var->val.TYPE

/* Grab numeric value of an argument, must be
 * known to be numeric */
#define INT_OR_FLT(X) \
	((X)->var->type == _INT ? (X)->var->val.INT : (X)->var->val.FLT)

/* Get the hell outta there */
#define ABORT(...) do {\
		printf("[ " _RED "ABORT" _RESET " ] "); \
		printf("saturn: "); \
		printf(__VA_ARGS__); \
		putchar('\n'); \
		End(); \
		exit(EXIT_FAILURE); \
	} while (0)

#ifdef DEBUG
#define DEBUGMSG(...) fprintf(stderr, __VA_ARGS__);
#else
#define DEBUGMSG(...)
#endif

/* Find the index o a string in an array of strings */
int arraystr(char **arr, int nmemb, char *str);

/* Replace all instances of old with new */
bool replace(char *str, char old, char new);
                              /* Screw sepples */
#endif
