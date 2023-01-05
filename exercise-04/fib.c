#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* initializes array for fib numbers */
    int input = atoi(argv[1]);
    long long *fib_numbers = malloc(input * sizeof(long long));

    fib_numbers[0] = 0;
    fib_numbers[1] = 1;

    /* calculate fib numbers */
    for (int i = 2; i<=input; i++) {
        fib_numbers[i] = fib_numbers[i-2] + fib_numbers[i-1];
    }

    printf("%lld\n" ,fib_numbers[input]);

    /* free the space occupied by the array */
    free(fib_numbers);
    return 0;
}
