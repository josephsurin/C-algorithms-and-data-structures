#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int top;
    size_t el_size, capacity;
    void* arr;
} Stack;

Stack* create_stack(size_t capacity, size_t el_size) {
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->top = 0;
    s->el_size = el_size;
    s->capacity = capacity;
    s->arr = calloc(capacity, el_size);
    return s;
}

int is_full(Stack* s) {
    return s->top == s->capacity;
}

int is_empty(Stack* s) {
    return s->top == 0;
}

int push(Stack* s, void* item) {
    if(is_full(s)) {
        return 0;
    }
    char* A = s->arr; 
    memcpy(A+(s->top * s->el_size), item, s->el_size);
    s->top++;
    return 1;
}

void* pop(Stack* s) {
    if(is_empty(s)) {
        return NULL;
    }
    char* A = s->arr;
    s->top--;
    void* item = A+(s->top * s->el_size);
    return item;
}

void* peek(Stack* s) {
    if(is_empty(s)) {
        return NULL;
    }
    char* A = s->arr;
    return A+((s->top - 1) * s->el_size);
}

int main(void) {
    Stack* s = create_stack(3, sizeof(char));
    char A = 'A', B = 'B', C = 'C';
    push(s, &A);
    printf("push and pop test 1: %c\n", *(char*)pop(s));
    push(s, &A);
    push(s, &B);
    printf("push and peek test: %c\n", *(char*)peek(s));
    push(s, &C);
    printf("push and pop test 2: %c\n", *(char*)pop(s));
    push(s, &A);
    printf("stack overflow test: 0 == %d\n", push(s, &A));
    return 0;
}
