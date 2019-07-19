# Stack

A stack is a Last-In-First-Out data structure equipped with two main methods: `push` and `pop`. The most recent item to be added to the stack using the `push` method is the first to be removed using the `pop` method. A stack can be implemented using a singular array. An integer variable, `top` is used to keep track of the number of items in the stack so far, therefore also representing the index for the next item to be pushed to. When an item is pushed onto the stack, it is placed into the array position indexed by the `top` variable, and the `top` variable is incremented. When an item is popped, the `top` variable is first decremented, and then item at the array position indexed by the new `top` variable is returned.

#### Implementation:

```C
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
```
