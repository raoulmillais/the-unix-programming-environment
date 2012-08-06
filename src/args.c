/* args: echoes its arguments and info about main() */
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int i;

	printf("argc is: %i\n", argc);
	
	for (i = 0; i < argc; i++) {
		printf("argv[%i] is: %s\n", i, argv[i]);
	}

	return 0;
}
