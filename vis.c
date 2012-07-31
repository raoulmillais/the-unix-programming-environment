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

int
main(int argc, char *argv[])
{
	int c = EOF;
	int nchar = 0, i = 0, max = 0;
	char buf[MAXLEN] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	FILE *in = stdin, *out = stdout;

	if (argc > 1 && strstr(argv[1], "-s") == argv[1]) {
		if (argv[1][2] == '\0' || !isdigit(argv[1][2])) {
			printf("%s\n", "Usage: vis [-s]N");
			return 1;
		}

		nchar = atoi(argv[1] + 2);
		if (nchar == 0)
			printf("Usage: a positive integer must be supplied\n", nchar);
	}

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

	return 0;
}
