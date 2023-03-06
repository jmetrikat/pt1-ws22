#ifndef __ISTACK_H
#define __ISTACK_H

enum errorT { OK,
              NOT_INITIALIZED,
              EMPTY,
              NO_MEMORY };

enum valT { INT,
            FLOAT,
            NONE };

/* all operations set the error type in this variable */
extern enum errorT error;

typedef struct stackElem *stackElemPtrT;
typedef struct _stack {
    stackElemPtrT top;
} *Stack;

typedef struct number {
    enum valT discr;
    union {
        int as_int;
        float as_float;
    };
} numberT;

extern numberT null_number;

typedef struct stackElem {
    numberT val;
    stackElemPtrT next;
    stackElemPtrT prev;
} stackElemT;

/* puts a new integer on top of the stack */
void push(Stack, numberT);
/* removes the integer at the top of the stack */
numberT pop(Stack);
/* peeks at the top of the stack without removing it */
numberT top(Stack);
/* swaps the two top-most elements of the stack */
void swap(Stack);

/* allocates a new stack */
Stack allocStack();
/* frees all memory associated with the stack */
void freeStack(Stack);

#endif
