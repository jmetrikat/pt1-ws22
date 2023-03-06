
#include "grading_table.h"

#include <stdio.h>
#include <stdlib.h>

/* read datastream and save elements in list */
grading_table_ptr read_list(FILE *fp) {
    grading_table_ptr startp = NULL;
    grading_table_ptr currp = NULL;

    union {
        char bytes[8];
        struct {
            uint32_t matrikelnummer;
            uint16_t serie;
            uint16_t punkte;
        };
    } buf;

    /* read 8 bytes at once with fread() */
    while (fread(buf.bytes, 8, 1, fp) > 0) {
        grading_table_ptr newp = (grading_table_ptr)malloc(sizeof(struct grading_entry_t));
        newp->next = NULL;

        /* copy data from buffer to new list element */
        newp->matrikelnummer = buf.matrikelnummer;
        newp->serie = buf.serie;
        newp->punkte = buf.punkte;

        /* when list is empty,  mark first  element as start */
        if (startp == NULL) {
            startp = newp;
            currp = newp;
        /* otherwise, append new element to list */
        } else {
            currp->next = newp;
            currp = newp;
        }
    }

    return startp;
}

/* free all elements in list */
void delete_list(grading_table_ptr head) {
    while (head->next) {
        grading_table_ptr tmp = head->next;
        free(head);
        head = tmp;
    }

    return;
}

/* call function for each element in list */
void traverse_list(grading_table_ptr head, void (*visitor)(grading_table_ptr current)) {
    while (head) {
        (*visitor)(head);
        head = head->next;
    }

    return;
}

/* call function for each element in list and use return value as value for next call */
int reduce_list(grading_table_ptr head, int (*visitor)(grading_table_ptr current, int val), int start_val) {
    int val = start_val;

    for (grading_table_ptr curr = head; curr != NULL; curr = curr->next) {
        val = (*visitor)(curr, val);
    }

    return val;
}
