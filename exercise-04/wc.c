#include <stdio.h>

int main (int argc, char *argv[]) {
    char c;
    int line_count = 0;
    int word_count = 0;
    int char_count = 0;
    int is_space = 1;

    /*endless loop until*/
    while(1) {
        c = getchar();
        
        /*break if end of file is reached*/
        if (c == EOF) {
            break;
        }
        
        /* treat all ascii < 32 as whitespaces*/
        else if(c <= 32) {
            if(c=='\n') {
                line_count++;
            }
            is_space = 1;
        }
        /**/
        else {
            if(is_space == 1) {
                word_count++;
                is_space = 0;
            }
        }
        char_count++;
    }

    /*print calculated scores*/
    printf("%d %d %d\n" , line_count, word_count, char_count);
    return 0;
}