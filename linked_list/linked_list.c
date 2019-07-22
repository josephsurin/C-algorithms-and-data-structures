#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void print_char(void* d) {
    char* c = (char*) d;
    printf(" %c ", *c);
}

int main(void) {
    LinkedList* l = create_linkedlist();
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
    return 0;
}
