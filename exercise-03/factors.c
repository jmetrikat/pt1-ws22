#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);
    for (int i = 1; i < input; i++) {
        if (input % i == 0) {
            printf("%d\n", i);
        }
    }

    return 0;
}
