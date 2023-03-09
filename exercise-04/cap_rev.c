#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <word1> [<word2> ...]\n", argv[0]);
		return 1;
	}

	/* iterate over every word given on command line */
	for (int v = argc - 1; v > 0; v--) {
		/* reverse the word in place */
		for (int i = 0, j = strlen(argv[v]) - 1; i <= j; i++, j--) {
			char c = toupper(argv[v][i]);
			argv[v][i] = toupper(argv[v][j]);
			argv[v][j] = c;
		}

		/* print the reversed word */
		printf("%s\n", argv[v]);
	}

	return 0;
}
