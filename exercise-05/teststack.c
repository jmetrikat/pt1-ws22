#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "istack.h"

#define LEN 80

/* prints the overall error on the screen */
void print_error() {
    printf("error = %d\n", error);
}

/* reads a command from the input and parses it into a command string and a generalized number */
void get_input(char *command[], numberT *val) {
    static char buf[LEN];
    int i;

    /* read the value from stdin */
    *val = null_number;
    fgets(buf, LEN, stdin);
    /* terminate it at the maximum size of the buffer (in case the user typed too many characters) */
    buf[LEN - 1] = '\0';

    /* assuming the command starts right away, terminate the string with a '\0' at the first whitespace */
    for (i = 0; i < LEN; i++)
        if (isspace(buf[i])) {
            buf[i] = '\0';
            break;
        }

    /* now keep scanning until there is a non-whitespace character ... */
    for (i++; i < LEN; i++)
        if (!isspace(buf[i]))
            break;

    /* ... and parse the rest as an integer */
    if (i < LEN) {
        /* search for a dot in the string */
        int j;
        for (j = i; j < LEN && buf[j] != '.'; j++)
            ;

        if (buf[j] == '.') {
            val->discr = FLOAT;
            val->as_float = atof(&buf[i]);
        } else {
            val->discr = INT;
            val->as_int = atoi(&buf[i]);
        }
    }
    *command = buf;

    return;
}

/* main entry point of the code */
int main(void) {
    int cont = 1;
    Stack s = NULL;

    /* endless loop until the continue flag is set to 0 */
    while (cont) {
        char *command;
        numberT val;

        /* print command list on screen and get new input */
        printf("init | push <int> | pop | swap | top | free | quit\n");
        get_input(&command, &val);

        /* handle all commands with istack functions */
        if (strcmp(command, "init") == 0) {
            if (s)
                printf("already initialized\n");
            else
                s = allocStack();
        } else if (strcmp(command, "push") == 0) {
            push(s, val);
        } else if (strcmp(command, "pop") == 0) {
            val = pop(s);
            if (error == OK)
                switch (val.discr) {
                    case INT:
                        printf("pop: value = (int) %d\n", val.as_int);
                        break;
                    case FLOAT:
                        printf("pop: value = (float) %f\n", val.as_float);
                        break;
                    default:
                        printf("pop: incorrect type\n");
                        break;
                }
        } else if (strcmp(command, "swap") == 0) {
            swap(s);
        } else if (strcmp(command, "top") == 0) {
            val = top(s);
            if (error == OK)
                switch (val.discr) {
                    case INT:
                        printf("top: value = (int) %d\n", val.as_int);
                        break;
                    case FLOAT:
                        printf("top: value = (float) %f\n", val.as_float);
                        break;
                    default:
                        printf("top: incorrect type\n");
                        break;
                }
        } else if (strcmp(command, "free") == 0) {
            freeStack(s);
            s = (Stack)0;
        } else if (strcmp(command, "quit") == 0) {
            cont = 0;
        } else {
            printf("wrong command!\n");
        }
        print_error();
    }
}
