#include <stdio.h>

int main(int argc, char **argv) {
	if (argc == 1) {
		puts("Hello world!");
		return 0;
	}

	for (int i = 0; i < argc; ++i)
		printf("argv[%d] = %s\n", i, argv[i]);
	
	return 0;
}

