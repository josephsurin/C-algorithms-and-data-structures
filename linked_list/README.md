# Linked List

A linked list is a data structure composed of a collection of nodes that form a sequence. Each node is a structure containing two fields: `data` and `next`. The `data` field holds the data being stored, and the `next` field is a pointer to the next node in the sequence. Basic operations include: `add`, `prepend`, `get_head`, `get_tail`, `remove`, `remove_head`, `remove_tail`, `find`, `traverse`. Operations such as `remove` and `find` have worst case time complexity of `O(n)` as all nodes may need to be iterated over. Unless a `tail` node is kept track of, this is also the case for `add` and `get_tail`.

A linked list can be implemented as a structure containing `head`, `tail`, fields.

#### `add`

When an element is added to the list (add to the end of the list), the `tail` node is modified to point to the new node, and the `tail` pointer is set to the new node. If it is the first element to be added, the `head` pointer is also set to point to this new node.

#### `prepend`

When an element is prepended to the list (add to the start of the list), the new node is created such that it points to the current `head`. The `head` pointer is then set to point to this new node. If it is the first element to be added, the `tail` pointer is also set to point to this new node.

#### `get_head`

Returns the data stored in the `head` node, if it exists.

#### `get_tail`

Returns the data stored in the `tail` node, if it exists.

#### `remove`

A pointer to the data to be removed must be provided. The list is iterated through in search of the node to be removed. Once found, the node before it is set to point to the node after it (the node being deleted).

#### `remove_head`

The `head` pointer is set to the node being pointed to by the current `head`.

#### `remove_tail`

The list is iterated until the 2nd last node is reached. This node is set to point to null, and the `tail` pointer is set to point to this node.

#### `find`

A pointer to the data being searched for must be provided. The list is iterated through in search of the node with the corresponding data. Once found, the node is returned.

#### `traverse`

An action is applied to all items in the list.

#### Implementation:

```C
struct Node_s {
    void* data;
    struct Node_s* next;
};

typedef struct Node_s Node;

typedef struct {
    Node *head, *tail;
} LinkedList;

LinkedList* create_linkedlist() {
    LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
    l->head = l->tail = NULL;
    return l;
}

void add(LinkedList* l, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if(l->tail == NULL) {
        l->head = l->tail = new_node;
    } else {
        l->tail->next = new_node;
        l->tail = new_node;
    }
}

void prepend(LinkedList* l, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    if(l->head == NULL) {
        l->head = l->tail = new_node;
    } else {
        new_node->next = l->head;
        l->head = new_node;
    }
}

void* get_head(LinkedList* l) {
    if(l->head == NULL) {
        return NULL;
    }
    return l->head->data;
}

void* get_tail(LinkedList* l) {
    if(l->tail == NULL) {
        return NULL;
    }
    return l->tail->data;
}

int remove_element(LinkedList* l, void* data) {
    if(l->head == NULL) {
        return 0;
    }
    Node* current = l->head;
    /* check if the target data is in the head node */
    if(current->data == data) {
        if(l->head == l->tail) {
            l->head = l->tail = NULL;
        } else {
            l->head = l->head->next;
        }
        return 1;
    }

    while(current->next != NULL) {
        if(current->next->data == data) {
            current->next = current->next->next;
            if(current->next->next == NULL) {
                l->head = current->next;
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}

int remove_head(LinkedList* l) {
    if(l->head == NULL) {
        return 0;
    }
    l->head = l->head->next;
    return 1;
}

int remove_tail(LinkedList* l) {
    if(l->tail == NULL) {
        return 0;
    }
    if(l->head == l->tail) {
        l->head = l->tail = NULL;
        return 1;
    }
    Node* current = l->head;
    while(current->next->next) {
        current = current->next;
    }
    l->tail = current;
    return 1;
}

Node* find(LinkedList* l, void* data) {
    if(l->head == NULL) {
        return NULL;
    }
    Node* current = l->head;
    while(current) {
        if(current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void traverse(LinkedList* l, void action(void*)) {
    if(l->head != NULL) {
        Node* current = l->head;
        do {
            action(current->data);
            current = current->next;
        } while(current != NULL);
    }
}
```
