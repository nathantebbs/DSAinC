#include "../include/stack.h"
#include <stdlib.h>

int stack_init(Stack* s, size_t init_cap) {
    if (!s)
        return -1;

    s->size = 0;
    s->cap  = init_cap ? init_cap : 16;
    s->data = (int*)malloc(s->cap * sizeof(int));

    return s->data ? 0 : -1;
}

void stack_free(Stack* s) {
    if (!s)
        return;

    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->cap  = 0;
}

int stack_push(Stack* s, int v) {
    if (!s)
        return -1;

    if (s->size == s->cap) {
        size_t new_cap = s->cap * 2;
        int*   p       = (int*)realloc(s->data, new_cap * sizeof(int));

        if (!p)
            return -1;

        s->data = p;
        s->cap  = new_cap;
    }

    s->data[s->size++] = v;
    return 0;
}

int stack_pop(Stack* s, int* out) {
    if (!s || s->size == 0)
        return -1;

    *out = s->data[--s->size];

    return 0;
}

int stack_empty(const Stack* s) {
    return !s || s->size == 0;
}
