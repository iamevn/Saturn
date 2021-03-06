#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "parse.h"
#include "instructions.h"
#include "util.h"

FILE *src_file;
extern char StatusWord;

int main(int argc, char **argv) {
	char line[81];
	char *comment = NULL;
	
	StatusWord = 0;

	if (argc == 2) {
		if (!strncmp(argv[1], "-V", 2) != !strncmp(argv[1], "--version", 9)) {
			print_version;
			return 0;
		}
		if (!strncmp(argv[1], "-h", 2) != !strncmp(argv[1], "--help", 6)) {
			print_help;
			return 0;
		}
		if (argv[1][0] == '-') {
			printf("Unrecognized option \'%s\'\nSee `%s -h for more information.\n",
			       argv[1], argv[0]);
			return 1;
		}

		src_file = fopen(argv[1], "r");
		if (!src_file) {
			fprintf(stderr, "saturn: error: %s: No such file or directory\n"
			                "saturn: fatal error: no input files\n"
			                "interpretation terminated.\n", argv[1]);
			exit(1);
		}
	} else {
		fprintf(stderr, "saturn: fatal error: no input files\n"
		                "interpretation terminated.\n");
		exit(1);
	}

	Init();
	Statement *instruction;

	/* start at the label `main' */
	Arg _main;
	_main.token = "main";
	saturn_jmp(&_main, NULL);

	// Begin processing source file
	for (int i = 0; !feof(src_file); i++) {
		fgets(line, 80, src_file);
		if (feof(src_file)) {
			break;
		}

		comment = strchr(line, ';');
		if (comment) {
			*comment = '\0';
		}

		if (line[0] == '#') {
			continue;
		}

		DEBUGMSG("%d: %s", i, line);	
		/* Parse line into a statement */
		instruction = Parse(line);

		/* Skip empty lines and labels*/
		if (instruction == NULL) {
			DEBUGMSG("<blank line or label>\n");
			free(instruction);
			continue;
		}

		/* Execute the instruction */
		Execute(instruction);

		/* Delete the statement, free all memory used for it and for literals */
		DeleteStatement(instruction);

	}

	fclose(src_file);

	End();
	return 0;
}
