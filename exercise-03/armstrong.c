#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i, current_num, sum, amount_of_digits, last_digit;
    int input;
    
    // read command line parameter
    if (argc == 2)
        input = atoi(argv[1]);
    else
        input = 0;

    // calculate armstrong numbers
    for(i=1; i<=input; i++) {
        sum = 0;
        // Copy the value of current_num for processing
        current_num = i;
        // check the amount of amount_of_digits of current_num
        amount_of_digits = (int) log10(current_num) + 1;

        /* Calculate sum of power of amount_of_digits */
        while(current_num > 0) {
            // only extract the last digit of current_num
            last_digit = current_num % 10;

            // Find sum of power of amount_of_digits
            // Use ceil() function to overcome any rounding errors by pow()
            sum = sum + ceil(pow(last_digit, amount_of_digits));

            // remove last digit to 
            current_num = current_num / 10;
        }

        // check if number really is armstrong number
        if(i == sum) {
            printf("%d\n", i);
        }
    }
    return 0;
}