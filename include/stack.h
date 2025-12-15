#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct {
    int*   data;
    size_t size;
    size_t cap;
} Stack;


int  stack_init(Stack* s, size_t init_cap);
void stack_free(Stack* s);
int  stack_push(Stack* s, int v);
int  stack_pop(Stack* s, int* out);
int  stack_empty(const Stack* s);

#endif // STACK_H
