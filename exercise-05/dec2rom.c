#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dec2rom(int number) {
    char *rom_chars[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int dec_vals[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    int i = 0;

    while (number > 0) {
        while (number >= dec_vals[i]) {
            printf("%s", rom_chars[i]);
            number -= dec_vals[i];
        }
        i++;
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <number1> [<number2> ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        dec2rom(atoi(argv[i]));
    }

    return 0;
}
