#include <stdio.h>
#include <string.h>

#include "grading_table.h"

void a(grading_table_ptr curr);
void b(grading_table_ptr curr);
int c(grading_table_ptr curr, int val);
int d(grading_table_ptr curr, int val);
int e(grading_table_ptr curr, int val);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s (a|b|c|d|e) [filename]\n", argv[0]);
        return 1;
    }

    FILE *fp = (argc == 3) ? fopen(argv[2], "r") : stdin;
    grading_table_ptr table_pt = read_list(fp);

    /* switch case to match argv[1] */
    switch (argv[1][0]) {
        case 'a':
            traverse_list(table_pt, a);
            break;
        case 'b':
            traverse_list(table_pt, b);
            break;
        case 'c':
            printf("%d\n", reduce_list(table_pt, c, 0));
            break;
        case 'd':
            printf("%d\n", reduce_list(table_pt, d, 0));
            break;
        case 'e':
            printf("%d\n", reduce_list(table_pt, e, 0));
            break;
        default:
            fprintf(stderr, "Invalid option: '%s'\n", argv[1]);
            return 1;
    }

    return 0;
}

void a(grading_table_ptr curr) {
    printf("%u hat in %u %u Punkt(e) erreicht.\n", curr->matrikelnummer, curr->serie, curr->punkte);
}

void b(grading_table_ptr curr) {
    if (curr->punkte < 10) {
        printf("%u %u\n", curr->matrikelnummer, curr->serie);
    }
}

int c(grading_table_ptr curr, int val) {
    return ++val;
}

int d(grading_table_ptr curr, int val) {
    if (curr->punkte > val) {
        return curr->punkte;
    }

    return val;
}

int e(grading_table_ptr curr, int val) {
    if (curr->serie == 3) {
        val += curr->punkte;
    }

    return val;
}
