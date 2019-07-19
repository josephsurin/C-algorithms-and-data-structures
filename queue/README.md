# Queue

A queue is a First-In-First-Out data structure equipped with two main methods: `enqueue` and `dequeue`. The first element to be added to the queue using the `enqueue` method will be the first to be removed using the `dequeue` method. A queue can be implemented using a single array with a circular structure to avoid the need to shuffle elements. Integer variables in `Z/cZ` (where `c` is the capacity of the queue) will be used to keep track of the start and end of the queue. Initially, the `start` variable is set to `0` and the `end` variable will be set to `c - 1` where `c` is the capacity of the queue. When an item is enqueued, if the queue is not already full, the `end` variable is incremented and the new item is inserted there. Upon dequeuing, the item pointed to by the `start` variable is removed and the `start` variable is incremented, while the `len` variable is decremented.

#### Implementation:

```C
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
```
