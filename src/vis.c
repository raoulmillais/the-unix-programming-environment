/* vis: make non-printable characters visible */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 9

int
isprintable(char c)
{
	if (isascii(c) && isprint(c) && c != ' ' && c != '\t' && c != '\n')
		return 1;

	return 0;
}

void
vis(FILE* in, int nchar)
{
	int c = EOF;
	int i = -1, max = 0;
	char buf[MAXLEN] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	FILE *out = stdout;

	while ((c = getc(in)) != EOF) {
		max = i = 1;
		if (isprintable(c))
			buf[0] = (char)c;

		/* seek ahead grabbing up to nchar printable characters */
		while (i < nchar) {
			c = getc(in);
			if (c == EOF || !isprintable(c)) {
				break;
			} else {
				buf[i] = (char)c;
				i++;
			}
		}
		buf[i] = '\0';

		/* if we got nchar printable characters and the buffer is not empty
		 * print the buffer and keep printing until EOF or an unprintable
		 * character */
		if (i >= nchar && buf[0] != '\0') {
			printf(buf);
			while ((c = getc(in)) != EOF && isprintable(c)) {
				putc(c, out);
			}
			putc(' ', out);
		}

		/* empty the buffer */
		for (max = i, i = 0; i < max; i++) {
			buf[i] = '\0';
		}
	}
}

int
main(int argc, char *argv[])
{
	int nchar = 0, i = 0;
	char buf[MAXLEN] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	FILE *in = stdin, *out = stdout;

	/* process -s switch and value as first argument if present */
	if (argc > 1 && strstr(argv[1], "-s") == argv[1]) {
		if (argv[1][2] == '\0' || !isdigit(argv[1][2])) {
			fprintf(stderr, "%s\n", "Usage: vis [-sX] [file1 ...]");
			return 1;
		}

		nchar = atoi(argv[1] + 2);
		if (nchar == 0) {
			fprintf(stderr, "Usage: a positive integer must be supplied\n");
			return 1;
		}
	}

	/* -sX only or other arguments - use stdin */
	if ((argc == 2 & nchar > 0) || argc == 1) {
		vis(stdin, nchar);
		return 0;
	}

	/* process all remaining arguments as filenames */
	if (argc > 1) {
		for (i = (nchar == 0) ? 1 : 2; i < argc; i++) {
			if ((in = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "Unable to open file: %s\n", argv[i]);
				continue;
			}

			vis(in, nchar);

			if (fclose(in) == EOF) {
				fprintf(stderr, "Unable to close file: %s\n", argv[i]);
				continue;
			}
		}

		return 0;
	}

	/* shouldn't get here */
	return 666;
}
