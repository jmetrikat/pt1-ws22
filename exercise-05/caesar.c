#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* encrypt string using caesar cipher */
void caesar(char *str, int shift) {
    char encr_char;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            encr_char = (str[i] - 'a'+ shift) % 26 + 'a';
            while (encr_char < 'a') {
                encr_char += 26;
            }
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            encr_char = (str[i] - 'A' + shift) % 26 + 'A';
            while (encr_char < 'A') {
                encr_char += 26;
            }
        } else {
            encr_char = str[i];
        }

        printf("%c", encr_char);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int shift = 0;
    size_t bufsize = 64;
    char *buffer = (char *)malloc(bufsize * sizeof(char));

    if (strcmp(argv[1], "encrypt") == 0) {
        getline(&buffer, &bufsize, stdin);
        shift = atoi(argv[2]);

    } else if (strcmp(argv[1], "decrypt") == 0) {
        getline(&buffer, &bufsize, stdin);
        shift = -atoi(argv[2]);

    } else {
        fprintf(stderr, "Usage: %s encrypt|decrypt <shift>\n", argv[0]);
        return 1;
    }

    caesar(buffer, shift);
    free(buffer);

    return 0;
}
