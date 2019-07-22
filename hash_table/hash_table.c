#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int main(void) {
    HashTable* h = create_hashtable(5);
    char* k1 = "key1"; char* v1 = "value1";
    char* k2 = "key2"; char* v2 = "value2";
    char* k3 = "key3"; char* v3 = "value3";
    char* k4 = "key4"; char* v4 = "value4";
    set(h, k1, v1);
    printf("set and get test 1: (%s, %s)\n", (char*)get(h, k1)->key, (char*)get(h, k1)->val);
    set(h, k2, v2);
    printf("set and get test 2: (%s, %s)\n", (char*)get(h, k2)->key, (char*)get(h, k2)->val);
    printf("delete and get test 1: deleting %s, deleted %s == %d\n", k1, k1, delete(h, k1));
    void* get_k1 = get(h, k1);
    printf("get deleted k1: NULL == %s\n", get_k1 ? "?" : "NULL");
    return 0;
}
