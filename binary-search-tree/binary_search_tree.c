#include <stdio.h>
#include <stdlib.h>

struct Node_s {
    void* key;
    void* data;
    struct Node_s *left, *right, *parent;
};

typedef struct Node_s Node;

typedef int (*cmp_func)(void*, void*);

typedef struct {
    Node* root;
    cmp_func cmp;
} BinarySearchTree;

BinarySearchTree* create_bst(cmp_func cmp) {
    BinarySearchTree* bst = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    bst->cmp = cmp;
    bst->root = NULL;
    return bst;
}

int insert(BinarySearchTree* bst, void* key, void* data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->data = data;
    n->left = n->right = n->parent = NULL;
    if(bst->root == NULL) {
        bst->root = n;
        return 1;
    }

    int insert_helper(Node* root) {
        if(bst->cmp(key, root->key) <= 0) {
            if(root->left == NULL) {
                n->parent = root;
                root->left = n;
                return 1;
            } else {
                return insert_helper(root->left);
            }
        }

        if(bst->cmp(key, root->key) > 0) {
            if(root->right == NULL) {
                n->parent = root;
                root->right = n;
                return 1;
            } else {
                return insert_helper(root->right);
            }
        }
    }

    return insert_helper(bst->root);
}

Node* search(BinarySearchTree* bst, void* key) {
    if(bst->root == NULL || bst->cmp(key, bst->root->key) == 0) {
        return bst->root;
    }

    Node* search_helper(Node* root) {
        if(bst->cmp(key, root->key) == 0) {
            return root;
        }

        if(bst->cmp(key, root->key) < 0) {
            if(root->left == NULL) {
                return NULL;
            }
            return search_helper(root->left);
        }

        if(bst->cmp(key, root->key) > 0) {
            if(root->right == NULL) {
                return NULL;
            }
            return search_helper(root->right);
        }
    }

    return search_helper(bst->root);
}

Node* find_min(BinarySearchTree* bst, Node* root) {
    if(root == NULL) {
        root = bst->root;
    }
    if(root == NULL) {
        return NULL;
    }
    if(root->left == NULL) {
        return root;
    }
    return find_min(bst, root->left);
}

Node* find_max(BinarySearchTree* bst, Node* root) {
    if(root == NULL) {
        root = bst->root;
    }
    if(root == NULL) {
        return NULL;
    }
    if(root->right == NULL) {
        return root;
    }
    return find_max(bst, root->right);
}

int bst_remove(BinarySearchTree* bst, void* key) {
    Node* D = search(bst, key);
    if(D == NULL) {
        return 0;
    }

    int remove_helper(Node* D) {
        /* case 1: node has no children */
        if(D->left == NULL && D->right == NULL) {
            if(bst->cmp(key, D->parent->key) <= 0) {
                D->parent->left = NULL;
            } else {
                D->parent->right = NULL;
            }
            return 1;
        }

        /* case 2: node has one child */
        if(D->left != NULL && D->right == NULL) {
            D->key = D->left->key;
            D->data = D->left->data;
            D->left = D->left->left;
            D->right = D->left->right;
            return 1;
        }
        if(D->right != NULL && D->left == NULL) {
            D->key = D->right->key;
            D->data = D->right->data;
            D->left = D->right->left;
            D->right = D->right->left;
            return 1;
        }

        /* case 3: node has two children */
        Node* R = find_min(bst, D->right);
        D->key = R->key;
        D->data = R->data;
        return remove_helper(R);
    }

    return remove_helper(D);
}

int cmp_key(void* a, void* b) {
    int *A = a, *B = b;
    return *A - *B;
}

int main(void) {
    BinarySearchTree* bst = create_bst(cmp_key);
    int key1 = 8; char* val1 = "val1";
    int key2 = 9; char* val2 = "val2";
    int key3 = -4; char* val3 = "val3";
    int key4 = -14; char* val4 = "val4";
    int key5 = 94; char* val5 = "val5";
    int key6 = 0; char* val6 = "val6";
    insert(bst, &key1, val1);
    insert(bst, &key2, val2);
    insert(bst, &key3, val3);
    Node* s2 = search(bst, &key2);
    printf("search test: (%d, %s)\n", *(int*)s2->key, (char*)s2->data);
    insert(bst, &key5, val5);
    Node* m5 = find_max(bst, NULL);
    printf("find max test: (%d, %s)\n", *(int*)m5->key, (char*)m5->data);
    insert(bst, &key6, val6);
    int r3 = bst_remove(bst, &key3);
    printf("remove test p1: %d\n", r3);
    Node* r3N = search(bst, &key3);
    printf("remove test p2, k3 found: %p\n", r3N);
    insert(bst, &key4, val4);
    Node* m4 = find_min(bst, NULL);
    printf("find min test: (%d, %s)\n", *(int*)m4->key, (char*)m4->data);
    return 0;
}
