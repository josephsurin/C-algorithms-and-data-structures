#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MIN(x,y) ((x) > (y) ? (y) : (x))

typedef struct animal_s animal_t;
void print_animals(animal_t*, int n);
int cmp_by_id(void*, void*);
void* copy_array(void*, int, size_t);

void swap(void* x, void* y, size_t size) {
    char *X = x, *Y = y;
    while(size--) {
        char b = *X;
        *X++ = *Y;
        *Y++ = b;
    }
}

void* insertion_sort(void* A, int n, size_t size, int cmp(void*, void*)) {
    char* cA = A;
    for(int i = 1; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(cmp(cA+j*size, cA+(j-1)*size) < 0) {
                swap(cA+j*size, cA+(j-1)*size, size);
            }
        } 
    }
    return A;
}

void* bubble_sort(void* A, int n, size_t size, int cmp(void*, void*)) {
    char* cA = A;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-1-i; j++) {
            if(cmp(cA+j*size, cA+(j+1)*size) > 0) {
                swap(cA+j*size, cA+(j+1)*size, size);
            }
        }
    }
    return A;
}

void* selection_sort(void* A, int n, size_t size, int cmp(void*, void*)) {
    char* cA = A;
    for(int i = 0; i < n-1; i++) {
        void* current_min = A+i*size;
        for(int j = i+1; j < n; j++) {
            if(cmp(A+j*size, current_min) < 0) {
                current_min = A+j*size;
            }
        }
        swap(current_min, A+i*size, size);
    }
    return A;
}

void* merge_sort(void* A, int n, size_t size, int cmp(void*, void*)) {
    void merge(void* A, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        char* L = (char*)malloc(n1*size);
        char* R = (char*)malloc(n2*size);
        memcpy(L, A+l*size, size*n1);
        memcpy(R, A+(m+1)*size, size*n2);
        int i = l;
        while(n1 && n2) {
            if(cmp(L, R) <= 0) {
                memcpy(A+i*size, L, size);
                L += size; n1--;
            } else {
                memcpy(A+i*size, R, size);
                R += size; n2--;
            }
            i++;
        }
        if(n1) {
            while(n1) {
                memcpy(A+i*size, L, size);
                L += size; i++; n1--;
            }
        } else if(n2) {
            while(n2) {
                memcpy(A+i*size, R, size);
                R += size; i++; n2--;
            }
        }
    }
    void mergesort_helper(char* A, int l, int r) {
        if(l < r) {
            int m = (l+r)/2;
            mergesort_helper(A, l, m);
            mergesort_helper(A, m + 1, r);
            merge(A, l, m, r);
        }
    }
    mergesort_helper(A, 0, n);
    return A;
}

void* quick_sort(void* A, int n, size_t size, int cmp(void*, void*)) {
    char* cA = A;
    int partition(int l, int h) {
        char* pivot = (char*)malloc(size);
        assert(pivot != NULL);
        memcpy(pivot, cA+((l+h)/2)*size, size); /* parentheses are important! */
        while(1) {
            while(cmp(cA+l*size, pivot) < 0) l++;
            while(cmp(cA+h*size, pivot) > 0) h--;
            if(l >= h) {
                free(pivot);
                return h;
            }
            swap(cA+l*size, cA+h*size, size);
            l++; h--;
        }
    }
    void* qsort(int l, int h) {
        if(l < h) {
            int p = partition(l, h);
            qsort(l, p);
            qsort(p+1, h);
        }
        return cA;
    }
    return qsort(0, n-1);
}

struct animal_s {
    int db_id;
    char name[30];
};

int main(void) {
    animal_t animals[] = {{ 3, "cat" }, { 99, "dragon" }, { -7, "bear" }, { 11, "cockroach" }, { 9, "dog" }, { 13, "turtle" }, { 47, "bird" }};
    size_t N = sizeof(animals)/sizeof(*animals);
    size_t S = sizeof(animal_t);
    printf("[ - ] Input Array: "); print_animals(animals, N);
    printf("[ * ] Insertion Sort: "); print_animals(insertion_sort(copy_array(animals, N, S), N, S, cmp_by_id), N);
    printf("[ * ] Bubble Sort: "); print_animals(bubble_sort(copy_array(animals, N, S), N, S, cmp_by_id), N);
    printf("[ * ] Selection Sort: "); print_animals(selection_sort(copy_array(animals, N, S), N, S, cmp_by_id), N);
    printf("[ * ] Merge Sort: "); print_animals(merge_sort(copy_array(animals, N, S), N, S, cmp_by_id), N);
    printf("[ * ] Quick Sort: "); print_animals(quick_sort(copy_array(animals, N, S), N, S, cmp_by_id), N);
    return 0;
}

void* copy_array(void* A, int n, size_t size) {
    char* B = (char*)malloc(size*n);    
    assert(B != NULL);
    char* cA = A;
    for(int i = 0; i < n*size; i++) {
        B[i] = cA[i];
    }
    return B;
}

void print_animals(animal_t animals[], int n) {
    for(int i = 0; i < n-1; i++) {
        printf("(%d, %s) ", animals[i].db_id, animals[i].name);
    }
    printf("(%d, %s)\n", animals[n-1].db_id, animals[n-1].name);
}

int cmp_by_id(void* a1, void* a2) {
    animal_t *A = a1, *B = a2;
    return A->db_id - B->db_id;
}
