#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    long i, j, input, fac;
    
    // read command line parameter
    if (argc == 2)
        input = atoi(argv[1]);
    else
        input = 0;

    // ask the user for input
    // printf("Please enter a number:\n");
    // scanf("%d", &input);

    // calculate faculty
    fac = input;
    for(int i = 1; i < input; i++) {
        fac = fac * i;
    }

    // create boolean array
    bool is_not_prime[fac + 1];
    
    for (int i = 0; i <= fac; i++) {
        is_not_prime[i] = false;
    }
    
    // Sieve of Eratosthenes -> pre-calculate primes
    is_not_prime[0] = is_not_prime[1] = true;
    for (int i = 2; i <= fac; i++) {
        if (!is_not_prime[i]) {
            for (int j = i * 2; j <= fac; j = j + i) {
                is_not_prime[j] = true;
            }
        }
    }
    
    // special case: fac == 1
    if (fac == 1 || fac == 0){
        printf("%ld is not prime.\n", fac);
    }

    // case: fac is prime
    else if (!is_not_prime[fac]) {
        printf("%ld is prime.\n", fac);
    }

    // case: fac is not prime and not 1
    else if (is_not_prime[fac]){
        
        // calculate maximum amount of factors
        int maxFactors = (int) ceil(log10(fac) / log10(2));
        // create new array to save factors
        int tmpArr [maxFactors];
        // count # of factors, used for output later    
        int countFactors = 0;

        // calculate all the factors
        for (int j = 2; j <= fac; j++) {
            if (fac % j == 0) {
                tmpArr[countFactors++] = j;
                fac = fac / j;
                j--;
            }  
        }

        // print all calculated factors
        int temp = tmpArr[0];
        for (int i = 1; i <= (countFactors - 1); i++) {
            printf("%d\n", temp);
            temp = tmpArr[i];
        }

        // print last factor separately to avoid '*' at the end 
        int lastFactor = tmpArr[countFactors - 1];
        printf("%d\n", lastFactor);
    }
}