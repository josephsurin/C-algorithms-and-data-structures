#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void* key;
    void* data;
} Node;

typedef int (*cmp_func)(void*, void*);

typedef struct {
    size_t size, capacity;
    cmp_func cmp;
    Node** nodes;
} Heap;

int get_left_child_index(int n) { return 2*n + 1; }
int get_right_child_index(int n) { return 2*n + 2; }
int get_parent_index(int n) { return (n - 1) / 2; }
int in_heap(Heap* h, int n) { return 0 <= n && n < h->size; }

void swap(void* x, void* y, size_t size) {
    char *X = x, *Y = y;
    while(size--) {
        char b = *X;
        *X++ = *Y;
        *Y++ = b;
    }
}

int sift_up(Heap* h, int n) {
    if(n == 0) return 0;
    void* n_key = h->nodes[n]->key;
    int p_index = get_parent_index(n);
    void* p_key = h->nodes[p_index]->key;
    if(h->cmp(n_key, p_key) <= 0) return 0;
    swap(h->nodes[n], h->nodes[p_index], sizeof(Node));
    sift_up(h, p_index);
    return 1;
}

int sift_down(Heap* h, int n) {
    void* n_key = h->nodes[n]->key;
    int l_index = get_left_child_index(n);
    int r_index = get_right_child_index(n);
    int h_index;

    if((!in_heap(h, l_index) || h->cmp(n_key, h->nodes[l_index]->key) >= 0)
            && (!in_heap(h, r_index) || h->cmp(n_key, h->nodes[r_index]->key) >= 0)) {
        return 0;
    }

    if((in_heap(h, l_index) && h->cmp(n_key, h->nodes[l_index]->key) < 0)
            && (!in_heap(h, r_index) || h->cmp(n_key, h->nodes[r_index]->key) >= 0)) {
        h_index = l_index;
    } else if((in_heap(h, r_index) && h->cmp(n_key, h->nodes[r_index]) < 0)
                && (!in_heap(h, l_index) || h->cmp(n_key, h->nodes[l_index]->key) >= 0)) {
        h_index = r_index;
    } else {
        h_index = h->cmp(h->nodes[l_index]->key, h->nodes[r_index]->key) > 0 ? l_index : r_index;
    }

    swap(h->nodes[n], h->nodes[h_index], sizeof(Node));
    sift_down(h, h_index);
    return 1;
}

Heap* create_heap(size_t capacity, int cmp(void*, void*)) {
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->capacity = capacity;
    h->size = 0;
    h->cmp = cmp;
    h->nodes = (Node**) calloc(capacity, sizeof(Node));
    return h;
}

int insert(Heap* h, void* key, void* data) {
    if(h->size >= h->capacity) {
        return 0;
    }
    Node* n = (Node*) malloc(sizeof(Node));
    n->key = key;
    n->data = data;
    h->nodes[h->size] = n;
    sift_up(h, h->size);
    h->size++;
    return 1;
}

int find(Heap* h, void* key) {
    for(int i = 0; i < h->size; i++) {
        if(h->cmp(key, h->nodes[i]->key) == 0) {
            return i;
        }
    }
    return -1;
}

int delete(Heap* h, void* key) {
    int targ_index = find(h, key);
    if(targ_index == -1) return 0;
    swap(h->nodes[targ_index], h->nodes[h->size-1], sizeof(Node));
    h->size--;
    sift_down(h, targ_index);
    return 1;
}

Node* find_max(Heap* h) {
    if(h->size == 0) return NULL;
    return h->nodes[0];
}

Node* pop(Heap* h) {
    if(h->size == 0) return NULL;
    swap(h->nodes[0], h->nodes[h->size-1], sizeof(Node));
    h->size--;
    sift_down(h, 0);
    return h->nodes[h->size];
}

void print_heap_arr(Heap* h) {
    for(int i = 0; i < h->size; i++) {
        printf("(%d, %s) ", *(int*)h->nodes[i]->key, h->nodes[i]->data);
    }
    printf("\n");
}

int int_cmp(void* a, void* b) {
    int *A = a, *B = b;
    return *A - *B;
}

int main(void) {
    Heap* h = create_heap(6, int_cmp);
    int key1 = 7; char* data1 = "data1";
    int key2 = 5; char* data2 = "data2";
    int key3 = 3; char* data3 = "data3";
    int key4 = 9; char* data4 = "data4";
    int key5 = -3; char* data5 = "data5";
    int key6 = 99; char* data6 = "data6";
    insert(h, &key1, data1);
    printf("insert and find max test: (%d, %s)\n", *(int*)find_max(h)->key, find_max(h)->data);
    insert(h, &key2, data2);
    insert(h, &key3, data3);
    insert(h, &key4, data4);
    insert(h, &key5, data5);
    printf("before pop: "); print_heap_arr(h);
    Node* p = pop(h);
    printf("insert and pop test: (%d, %s)\n", *(int*)p->key, p->data);
    printf("after pop: "); print_heap_arr(h);
    printf("before delete: "); print_heap_arr(h);
    printf("deleting key %d: %d\n", key3, delete(h, &key3));
    printf("after delete: "); print_heap_arr(h);
    return 0;
}
