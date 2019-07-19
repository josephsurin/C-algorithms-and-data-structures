#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int start, end;
    size_t len, el_size, capacity;
    void* arr;
} Queue;

Queue* create_queue(size_t capacity, size_t el_size) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->start = q->len = 0;
    q->end = capacity - 1;
    q->el_size = el_size;
    q->capacity = capacity;
    q->arr = calloc(capacity, el_size);
    return q;
}

int is_full(Queue* q) {
    return q->len == q->capacity;
}

int is_empty(Queue* q) {
    return q->len == 0;
}

int enqueue(Queue* q, void* item) {
    /* check that there is space */
    if(is_full(q)) {
        return 0;
    }
    q->end = (q->end + 1) % q->capacity;
    q->len++;
    char* A = q->arr;
    memcpy(A+(q->end * q->el_size), item, q->el_size);
    return 1;
}

void* dequeue(Queue* q) {
    if(is_empty(q)) {
        return NULL;
    }
    char* A = q->arr;
    void* item = A+(q->start * q->el_size);
    q->start++;
    q->len--;
    return item;
}

void* front(Queue* q) {
    if(is_empty(q)) {
        return NULL;
    }
    char* A = q->arr;
    return A+(q->start * q->el_size);
}

void* rear(Queue* q) {
    if(is_empty(q)) {
        return NULL;
    }
    char* A = q->arr;
    return A+(q->end * q->el_size);
}

int main(void) {
    Queue* q = create_queue(5, sizeof(char));
    char A = 'A', B = 'B', C = 'C', D = 'D';
    enqueue(q, &A);
    printf("enqueue and front peek test 1: %c\n", *(char*)front(q));
    enqueue(q, &B);
    printf("enqueue and front peek test 2: %c\n", *(char*)front(q));
    enqueue(q, &C);
    printf("enqueue and rear peek test: %c\n", *(char*)rear(q));
    enqueue(q, &D);
    printf("dequeue test 1: %c\n", *(char*)dequeue(q));
    printf("dequeue test 2: %c\n", *(char*)dequeue(q));
    enqueue(q, &A);
    enqueue(q, &A);
    enqueue(q, &A);
    printf("capacity check test: 0 == %d\n", enqueue(q, &A));
    return 0;
}
