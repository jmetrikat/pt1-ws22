#include <stdio.h>

int main (int argc, char *argv[]) {
    char c;
    int line_count = 0, word_count = 0, char_count = 0;
    int is_whitespace = 1;

    /* read all chars until EOF is reached */
    while((c = getchar()) != EOF) {
        /* treat all ascii < 32 as whitespaces*/
        if (c <= 32) {
            if (c=='\n') {
                line_count++;
            }
            is_whitespace = 1;

        /* current char is not whitespace */
        } else {
            /* previous char was whitespace */
            if (is_whitespace) {
                word_count++;
                is_whitespace = 0;
            }
        }
        char_count++;
    }

    /* print calculated scores */
    printf("%d %d %d\n" , line_count, word_count, char_count);
    return 0;
}
