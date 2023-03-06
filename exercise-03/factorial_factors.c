#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);

    /* compute the factorial */
    int fac = 1;
    for (int i = 1; i <= input; i++) {
        fac *= i;
    }

    /* check for prime */
    int factor = 2;

    while (fac != 1) {
        int is_prime = 1;

        for (int j = 2; j < factor; j++) {
            if (factor % j == 0) {
                is_prime = 0;
                break;
            }
        }

        if (fac % factor == 0 && is_prime) {
            fac /= factor;
            printf("%d\n", factor);
        }

        /* increment if the current number can't be factor */
        if (fac % factor != 0 || !is_prime) {
            factor++;
        }
    }

    return 0;
}
