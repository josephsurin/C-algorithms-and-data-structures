# Hash Table

A hash table is a data structure that maps keys to values, allowing for a very fast lookup operation. It can be implemented with an array and uses a hashing function to map the key (a string) to an index (a non-negative integer).

If the hashing function is imperfect (it most likely will be), then collisions may occur. A collision refers to two different keys being hashed into the same hash by the hash function. If this occurs, since both items can't occupy the same index, a workaround is required. One such workaround is to use a linked list as each element of the array, and append to the linked list at the appropriate index if a collision occurs. Ideally, all linked lists should be around the same size.

The main operations are: `set`, `delete` and `get`.

#### `set`

Given a key-value pair, the key is hashed and the key-value pair is appended to the linked list in the array at the index given by the hash. If the key already exists, the value is updated.

#### `delete`

Given a key, removes the associated key-value pair.

#### `get`

Given a key, returns the associated value if it exists in the hash table.

#### Implementation:

```C
#include "linked_list.c"

typedef struct {
    char* key;
    void* val;
} Key_Val;

typedef struct {
    size_t capacity;
    LinkedList** buckets;
} HashTable;

/* http://www.cse.yorku.ca/~oz/hash.html djb2 */
unsigned int hash(char* str, int M) {
    unsigned long hash = 5381;
    int c;
    while(c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    return (unsigned int)(hash % M);
}

int cmp_key(void* a, void* b) {
    Key_Val *A = a, *B = b;
    return strcmp(A->key, B->key);
}

HashTable* create_hashtable(size_t capacity) {
    HashTable* h = (HashTable*) malloc(sizeof(HashTable));
    h->capacity = capacity;
    h->buckets = (LinkedList**) malloc(capacity*sizeof(LinkedList*));
    for(int i = 0; i < capacity; i++) {
        LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
        h->buckets[i] = l;
    }
    return h;
}

int set(HashTable* h, char* key, void* val) {
    unsigned int key_hash = hash(key, h->capacity);
    LinkedList* bucket = h->buckets[key_hash];
    Key_Val* kv = (Key_Val*) malloc(sizeof(Key_Val));
    kv->key = key;
    kv->val = val;
    Node* node = linkedlist_find(bucket, kv, cmp_key);
    if(node == NULL) {
        linkedlist_add(bucket, kv);
        return 2;
    } else {
        node->data = kv;
        return 1;
    }
}

int delete(HashTable* h, char* key) {
    unsigned int key_hash = hash(key, h->capacity);
    LinkedList* bucket = h->buckets[key_hash];
    Key_Val* kv = (Key_Val*) malloc(sizeof(Key_Val));
    kv->key = key;
    Node* node = linkedlist_find(bucket, kv, cmp_key);
    if(node == NULL) {
        return 0;
    }
    linkedlist_remove_element(bucket, kv, cmp_key);
    return 1;
}

Key_Val* get(HashTable* h, char* key) {
    unsigned int key_hash = hash(key, h->capacity);
    LinkedList* bucket = h->buckets[key_hash];
    Key_Val* kv = (Key_Val*) malloc(sizeof(Key_Val));
    kv->key = key;
    Node* node = linkedlist_find(bucket, kv, cmp_key);
    if(node == NULL) {
        return NULL;
    }
    return (Key_Val*)node->data;
}
```
