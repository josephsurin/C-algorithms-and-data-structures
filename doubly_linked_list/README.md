# Doubly Linked List

A doubly linked list is a data structure similar to a singly linked list, except each node maintains a reference to the node before it and after it. This allows traversal in either direction. Basic operations include `add`, `prepend`, `get_head`, `get_tail`, `remove`, `remove_head`, `remove_tail`, `find`, `traverse`, `traverse_backwards`. Note that `remove_tail` is much more efficient as the list need not be traversed to find the second last element (as is the case with the singly linked list).

#### `add`

The `tail` node's `next` pointer is set to point to the new node, and the new node's `prev` pointer is set to point to the current `tail` node. The list's `tail` pointer is then set to point to the new node.

#### `prepend`

The `head` node's `prev` pointer is set to point to the new node, and the new node's `next` pointer is set to point to the current `head` node. The list's `head` pointer is then set to point to the new node.

#### `get_head`

Returns the data stored in the `head` node, if it exists.

#### `get_tail`

Returns the data store in the `tail` node, if it exists.

#### `remove`

Iterate over the list in search of the node to be removed. Once found, set the `next` pointer of the node behind it to point to the node after it, and set the `prev` pointer of the node after it to point to the node before it.

#### `remove_head`

Set the `head` pointer to the node given by the current `head`'s `next` pointer.

#### `remove_tail`

Set the `tail` pointer to the node given by the current `tail`'s `prev` pointer.

#### `find`

Iterate through the list until the corresponding node is found.

#### `traverse`

Starting from the `head` node, apply an action to all items in the list.

#### `traverse_backwards`

Starting from the `tail` node and ending at thee `head` node, apply an action to all items in the list.

#### Implementation:

```C
struct Node_s {
    void* data;
    struct Node_s *prev, *next;
};

typedef struct Node_s Node;

typedef struct {
    Node *head, *tail;
} DoublyLinkedList;

DoublyLinkedList* create_doublylinkedlist() {
    DoublyLinkedList* l = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    l->head = l->tail = NULL;
    return l;
}

void add(DoublyLinkedList* l, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = l->tail;
    if(l->tail == NULL) {
        l->head = l->tail = new_node;
    } else {
        l->tail->next = new_node;
        l->tail = new_node;
    }
}

void prepend(DoublyLinkedList* l, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    if(l->head == NULL) {
        l->head = l->tail = new_node;
    } else {
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
    }
}

void* get_head(DoublyLinkedList* l) {
    if(l->head == NULL) {
        return NULL;
    }
    return l->head->data;
}

void* get_tail(DoublyLinkedList* l) {
    if(l->tail == NULL) {
        return NULL;
    }
    return l->tail->data;
}

int remove_element(DoublyLinkedList* l, void* data) {
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

    while(current != NULL) {
        if(current->data == data) {
            if(current->next == NULL) { /* deleting the tail */
                current->prev->next = NULL;
                l->tail = current->prev;
                return 1;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int remove_head(DoublyLinkedList* l) {
    if(l->head == NULL) {
        return 0;
    }
    l->head = l->head->next;
    return 1;
}

int remove_tail(DoublyLinkedList* l) {
    if(l->tail == NULL) {
        return 0;
    }
    if(l->head == l->tail) {
        l->head = l->tail = NULL;
        return 1;
    }
    l->tail = l->tail->prev;
    return 1;
}

Node* find(DoublyLinkedList* l, void* data) {
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

void traverse(DoublyLinkedList* l, void action(void*)) {
    if(l->head != NULL) {
        Node* current = l->head;
        do {
            action(current->data);
            current = current->next;
        } while(current != NULL);
    }
}

void traverse_backwards(DoublyLinkedList* l, void action(void*)) {
    if(l->tail != NULL) {
        Node* current = l->tail;
        do {
            action(current->data);
            current = current->prev;
        } while(current != NULL);
    }
}
```
