#include "istack.h"

#include <stdlib.h>

/* defines the global error variable */
enum errorT error;

numberT null_number = {.discr = NONE};

/* puts a new integer on top of the stack */
void push(Stack s, numberT val) {
    /* checks that the stack is allocated */
    if (!s) {
        error = NOT_INITIALIZED;
        return;
    }

    /* allocates memory on the heap for the new element */
    stackElemPtrT pt = (stackElemPtrT)malloc(sizeof(stackElemT));
    if (!pt) {
        error = NO_MEMORY;
        return;
    }

    /* adds the value to the new stack element */
    pt->val = val;

    /* fixes the pointers of the new and old top */
    pt->prev = NULL;
    pt->next = s->top;
    if (s->top)
        s->top->prev = pt;

    /* makes the new element the new top */
    s->top = pt;
    error = OK;
    return;
}

/* removes the integer at the top of the stack */
numberT pop(Stack s) {
    /* checks that the stack is allocated */
    if (!s) {
        error = NOT_INITIALIZED;
        return null_number;
    }
    /* checks that there is at least one element on the stack */
    if (!s->top) {
        error = EMPTY;
        return null_number;
    }

    /* extracts the value */
    numberT rc = s->top->val;

    /* promotes the next element on the stack to the top of the stack */
    stackElemPtrT pt = s->top;
    s->top = s->top->next;
    if (s->top)
        s->top->prev = NULL;

    /* releases the memory for the popped element from the heap */
    free(pt);
    error = OK;

    return rc;
}

/* peeks at the top of the stack without removing it */
numberT top(Stack s) {
    /* checks that the stack is allocated */
    if (!s) {
        error = NOT_INITIALIZED;
        return null_number;
    }
    /* checks that there is at least one element on the stack */
    if (!s->top) {
        error = EMPTY;
        return null_number;
    }
    error = OK;
    return s->top->val;
}

/* swaps the two top-most elements of the stack */
void swap(Stack s) {
    /* checks that the stack is allocated */
    if (!s) {
        error = NOT_INITIALIZED;
        return;
    }
    /* checks that there is at least one element on the stack */
    if (!s->top) {
        error = EMPTY;
        return;
    }

    /* if there is at least a second element on the stack ... */
    if (s->top->next) {
        /* ... then swap them and fix up all the pointers */
        stackElemPtrT pt = s->top;
        s->top = s->top->next;

        s->top->prev = pt->prev;
        pt->prev = s->top;
        pt->next = s->top->next;
        s->top->next = pt;
    }
    error = OK;
    return;
}

/* allocates a new stack */
Stack allocStack() {
    /* allocates the root */
    Stack s = (Stack)malloc(sizeof(struct _stack));
    if (!s) {
        error = NO_MEMORY;
        return (Stack)0;
    }

    /* since the stack is empty, the first element is NULL */
    s->top = (stackElemPtrT)0;
    error = OK;
    return s;
}

/* frees all memory associated with the stack */
void freeStack(Stack s) {
    /* checks that the stack is allocated */
    if (!s) {
        error = NOT_INITIALIZED;
        return;
    }

    /* as long as there is a stack element ... */
    stackElemPtrT pt = s->top;
    while (pt) {
        /* ... save the pointer to next and free the memory */
        stackElemPtrT p2 = pt;
        pt = pt->next;
        free(p2);
    }

    /* finally, free the root element */
    free(s);
    error = OK;
    return;
}
