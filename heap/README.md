# Heap

A heap is a tree-based data structure that satisfies the heap property.

##### Heap property (max heap)

For any node `C`, if `P` is a parent node of `C` then the key of `P` is greater than or equal to the key of `C`.

##### Heap property (min heap)

For any node `C`, if `P` is a parent node of `C` then the key of `P` is less than or equal to the key of `C`.

In a max heap, the element with the largest key is always stored at the root. Basic operations include `insert`, `find`, `delete`, `find_max`, `pop` with internal functions `heapify`, `sift_up`, `sift_down`.

The heap can be implemented with a single array using the array index to reference parent/child nodes.

#### `insert`

Add the key-value pair (node) to the next empty position in the array, increment the size counter and sift up.

#### `find`

Linear search for the index of the node with the given key.

#### `delete`

Find the node with the given key, swap it with the node in the last non-empty position of the array, decrement the size counter and sift down.

#### `find_max`

Return the root node.

#### `pop`

Swap the root node with the node in the last non-empty position of the array, decrement the size counter, sift down and return the node in the final position (the node that was previously the root node)

#### `heapify`

Create a heap from an array; start from the last element in the array and continue sifting up until no more swaps occur.

#### `sift_up`

'Sift' a node (specified by array index) upwards so that it satisfies the heap condition. If the node is the root, or it is less than or equal to its parent, return false. Otherwise, swap it with its parent and call `sift_up` recursively at its new index.

#### `sift_down`

'Sift' a node (specified by array index) downwards so that it satisfies the heap condition. Check the node's left and right children. If the node is greater than both children, return false. (If a child does not exist, consider the parent to be greater than it). If the node is less than at least one of its children, find which of its children has the higher value and swap it with that child. Then recursively call `sift_down` at the node's new index.

#### Implementation:

```C
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
```
