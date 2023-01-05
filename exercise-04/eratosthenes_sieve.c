#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* get command line input and create dynamic array */
    int input = atoi(argv[1]);
    int *is_prime = malloc(input * sizeof(int));

    /* initalize the array with true */
    for (int i = 0; i < input; i++) {
        is_prime[i] = 1;
    }

    /* sieve of erathotstenes */
    for (int j = 2; j < input; j++) {
        if (is_prime[j] == 1) {
            for (int k = j * 2; k < input; k = k + j){
                is_prime[k] = 0;
            }
        }
    }

    /* print all primes */
    for (int l = 2; l < input; l++) {
        if (is_prime[l]) {
            printf("%d\n" ,l);
        }
    }

    /* free the space occupied by the array */
    free(is_prime);
    return 0;
}
