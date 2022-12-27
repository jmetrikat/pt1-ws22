#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int i, input;

    // read command line parameter
    if (argc == 2)
        input = atoi(argv[1]);
    else
        input = 0; 

    // ask the user for input
    // printf("Please enter a number:\n");
    // scanf("%d", &input);
    
    for(int i = 1; i < input; i++) {
        if(input%i == 0) {
            printf("%d\n", i);
        }
    }
    return 0;
}