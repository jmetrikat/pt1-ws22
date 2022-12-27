#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	/*iterate over every word given on command line*/
	for (int v=argc-1; v>0; v--){

		/* reverse the word in place */
        for (int i = 0, j = strlen(argv[v]) - 1; i <= j; i++, j--) {
			char c = toupper(argv[v][i]);
			argv[v][i] = toupper(argv[v][j]);
			argv[v][j] = c;
		}

		/*print the reversed word*/
        printf("%s\n", argv[v]);
    }
	return 0;
}
