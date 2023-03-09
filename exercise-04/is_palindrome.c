#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <word1> [<word2> ...]\n", argv[0]);
        return 1;
    }

    /* iterate over every command line parameter aka given word */
    for (int v = 1; v < argc; v++) {
        int is_palindrome = 1;

        /* check for current word from front to back if characters are matching */
        for (int i = 0; i < strlen(argv[v]); i++) {
            if (argv[v][i] != argv[v][strlen(argv[v]) - i - 1]) {
                printf("NO\n");
                is_palindrome = 0;
                break;
            }
        }

        /* given word is a palindrome */
        if (is_palindrome) {
            printf("YES\n");
        }
    }

    return 0;
}
