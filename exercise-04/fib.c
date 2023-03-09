#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    /* initialize array for fib numbers */
    int input = atoi(argv[1]);
    long long *fib = (long long *)malloc((input + 1) * sizeof(long long));

    fib[0] = 0;
    fib[1] = 1;

    /* calculate fib numbers */
    for (int i = 2; i <= input; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    printf("%lld\n", fib[input]);

    /* free the space occupied by the array */
    free(fib);
    return 0;
}
