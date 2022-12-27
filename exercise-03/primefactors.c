#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i, j, input;
    
    // read command line parameter
    if (argc == 2)
        input = atoi(argv[1]);
    else
        input = 0;

    // ask the user for input
    // printf("Please enter a number:\n");
    // scanf("%d", &input);

    // create boolean array
    bool is_not_prime[input + 1];
    for (int i = 0; i <= input; i++) {
        is_not_prime[i] = false;
    }
    
    // Sieve of Eratosthenes -> pre-calculate primes
    is_not_prime[0] = is_not_prime[1] = true;
    for (int i = 2; i <= input; i++) {
        if (!is_not_prime[i]) {
            for (int j = i * 2; j <= input; j = j + i) {
                is_not_prime[j] = true;
            }
        }
    }
    
    // special case: input == 1
    if (input == 1 || input == 0){
        printf("%d is not prime.\n", input);
    }

    // case: input is prime
    else if (!is_not_prime[input]) {
        printf("%d is prime.\n", input);
    }

    // case: input is not prime and not 1
    else if (is_not_prime[input]){        
        // calculate maximum amount of factors
        int maxFactors = (int) ceil(log10(input) / log10(2));
        // create new array to save factors
        int tmpArr [maxFactors];
        // count # of factors, used for output later    
        int countFactors = 0;

        // calculate all the factors
        for (int j = 2; j <= input; j++) {
            if (input % j == 0) {
                tmpArr[countFactors++] = j;
                input = input / j;
                j--;
            }  
        }

        // print all calculated factors
        int current = tmpArr[0];
        int previous;
        for (int i = 1; i <= countFactors; i++) {
            if(current != previous) {
                printf("%d\n", current);
            }
            previous = tmpArr[i-1];
            current = tmpArr[i];
        }
    }
}