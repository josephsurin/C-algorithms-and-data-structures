# Binary Search Tree

A binary search tree (BST) is a data structure that stores items as a key-value pair, always maintaining the order of the keys so that lookup and other operations can use binary search (to achieve logarithmic time).

A binary search tree is determined by its root node, who has a left subtree and a right subtree. The tree satisfies the _binary search_ property; the key in each node must be greater than or equal to any key in the left subtree, and less than or equal to any key in the right subtree.

The basic operations include `insert`, `search`, `remove`, `find_min`, `find_max`

#### `insert`

When an item is inserted (as a key-value pair), we first check if the tree is empty (that is, the root node is null). If it is, the root node is set to point to this newly inserted node. Then, we recursively check for the to-be-inserted node's correct position. The base case occurs when the left (or right) node is null, and the node is inserted there.

i.e. we first compare the keys of the root node and the node to be inserted. If the key of the node to be inserted is less than or equal to the root node's key, and the left subtree exists, we perform the insert on this subtree. Otherwise, we do the same except for the right subtree.

#### `search`

Firstly, check whether the root node exists, or if it does, whether the key being searched for is equal to the root node's key. If neither are the case, then we recursively check the tree based on the comparison between the root node and the search key.

#### `remove`

We first search for the node to be removed. Then, we consider the three cases:

- Case 1, node has no children: If the node has no children, we simply set the parent's (left or right, depending on the value of the node) pointer to null, essentially removing all references to the node from the tree.
- Case 2, node has one child: If the node's only child is its left child, then the the parent node is deleted and replaced with its child. That is, the parent node's key and value are changed to equal its child, and the parent's left and right child pointers are set to what its child's were previously.
- Case 3, node has two children: Choose the smallest element in the right subtree and replace the node to be deleted's key and value with it. Then the smallest element can easily be deleted as it satisfies case 1 or case 2.

#### `find_min`

Finds the minimum node in the tree using the principle that the minimum node does not have a left child (or else it would not be the minimum node).

#### `find_max`

Finds the maximum node in the tree using the principle that the maximum node does not have a right child (or else it would not be the maximum node).

#### Implementation:

```C
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
```
