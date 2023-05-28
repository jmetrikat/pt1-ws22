#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    /* check all numbers from 1 to input */
    int input = atoi(argv[1]);
    for (int i = 1; i < input; i++) {
        int no_digits = log10(i) + 1;

        int tmp = i;
        int sum = 0;
        while (tmp != 0) {
            int last_digit = tmp % 10;
            sum += pow(last_digit, no_digits);
            tmp /= 10;
        }

        if (sum == i) {
            printf("%d\n", i);
        }
    }

    return 0;
}
