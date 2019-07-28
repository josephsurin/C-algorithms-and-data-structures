#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void print_char(void* d) {
    char* c = (char*) d;
    printf(" %c ", *c);
}

int main(void) {
    DoublyLinkedList* l = create_doublylinkedlist();
    char A = 'A', B = 'B', C = 'C', D = 'D', E = 'E';
    add(l, &A);
    add(l, &B);
    printf("add and get_head test: %c\n", *(char*)get_head(l));
    prepend(l, &C);
    printf("prepend and get_head test: %c\n", *(char*)get_head(l));
    int r = remove_element(l, &C);
    printf("remove and get_head test: %d %c\n", r, *(char*)get_head(l));
    add(l, &C);
    add(l, &D);
    printf("add and find test: %c\n", *(char*)find(l, &C)->data);
    prepend(l, &E);
    printf("prepend and get_tail test: %c\n", *(char*)get_tail(l));
    printf("traverse test: ");
    traverse(l, print_char);
    printf("traverse backwards test: ");
    traverse_backwards(l, print_char);
    return 0;
}
