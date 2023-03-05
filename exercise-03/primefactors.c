#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);

    /* check for prime */
    for (int i = 2; i < input; i++) {
        int is_prime = 1;

        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }

        if (input % i == 0 && is_prime) {
            printf("%d\n", i);
        }
    }

    return 0;
}
