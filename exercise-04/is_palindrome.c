#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    /*iterate over every command line parameter aka given word*/
    for (int v = 1; v < argc; v++){
        int printed = 0;

        /*check for current word from front to back if characters are matching*/
        for (int i = 0; i < strlen(argv[v]); i++) {
            if (argv[v][i] != argv[v][strlen(argv[v]) - i - 1]){
                printf("NO\n");
                printed = 1;
                break;
            }
        }
        
        /*given word is a palindrome*/
        if (printed == 0){
            printf("YES\n");
        }
    }
    return 0;
}