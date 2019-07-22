struct Node_s {
    void* data;
    struct Node_s* next;
};

typedef struct Node_s Node;

typedef struct {
    Node *head, *tail;
    size_t el_size;
} LinkedList;

LinkedList* create_linkedlist(size_t el_size) {
    LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
    l->head = l->tail = NULL;
    l->el_size = el_size;
    return l;
}

void linkedlist_add(LinkedList* l, void* data) {
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

void linkedlist_prepend(LinkedList* l, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    if(l->head == NULL) {
        l->head = l->tail = new_node;
    } else {
        new_node->next = l->head;
        l->head = new_node;
    }
}

void* linkedlist_get_head(LinkedList* l) {
    if(l->head == NULL) {
        return NULL;
    }
    return l->head->data;
}

void* linkedlist_get_tail(LinkedList* l) {
    if(l->tail == NULL) {
        return NULL;
    }
    return l->tail->data;
}

int linkedlist_remove_element(LinkedList* l, void* data, int cmp(void*, void*)) {
    if(l->head == NULL) {
        return 0;
    }
    Node* current = l->head;
    /* check if the target data is in the head node */
    if(cmp(current->data, data) == 0) {
        if(l->head == l->tail) {
            l->head = l->tail = NULL;
        } else {
            l->head = l->head->next;
        }
        return 1;
    }

    while(current->next != NULL) {
        if(cmp(current->next->data, data) == 0) {
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

int linkedlist_remove_head(LinkedList* l) {
    if(l->head == NULL) {
        return 0;
    }
    l->head = l->head->next;
    return 1;
}

int linkedlist_remove_tail(LinkedList* l) {
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

Node* linkedlist_find(LinkedList* l, void* data, int cmp(void*, void*)) {
    if(l->head == NULL) {
        return NULL;
    }
    Node* current = l->head;
    while(current) {
        if(cmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void linkedlist_traverse(LinkedList* l, void action(void*)) {
    if(l->head != NULL) {
        Node* current = l->head;
        do {
            action(current->data);
            current = current->next;
        } while(current != NULL);
    }
}
