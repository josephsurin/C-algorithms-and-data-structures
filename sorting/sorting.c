#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN(x,y) ((x > y) ? y : x)

int* copy_array(int*, int);
void print_arr(int*, int);

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* insertion_sort(int A[], int n) {
    /* iterate from left to right */
    for(int i = 1; i < n; i++) {
        /* iterate from the item currently being examined to the start of the array */
        for(int j = i; j > 0; j--) {
            /* swap if the item currently being examined is less than the one to its left */
            if(A[j] < A[j-1]) {
                swap(&A[j], &A[j-1]);
            }
        }
    }
    return A;
}

int* bubble_sort(int A[], int n) {
    for(int i = 0; i < n; i++) {
        /* by the ith iteration, the last i items should already be sorted */
        for(int j = 0; j < n-1-i; j++) {
            if(A[j] > A[j+1]) {
                swap(&A[j], &A[j+1]);
            }
        }
    }
    return A;
}

int* selection_sort(int A[], int n) {
    for(int i = 0; i < n-1; i++) {
        int current_min = A[i]; /* minimum item in the unsorted subarray */
        int min_index = i;
        /* search the rest of the unsorted subarray for a smaller item */
        for(int j = i+1; j < n; j++) {
            if(A[j] < current_min) {
                current_min = A[j];
                min_index = j;
            }
        }
        swap(&A[min_index], &A[i]); /* move the smallest item in the unsorted subarray to the end of the sorted subarray */
    }
    return A;
}

int* merge_sort(int A[], int n) {
    void merge(int A[], int l, int m, int r) {
        int i;
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = malloc(sizeof(int)*n1);
        int* R = malloc(sizeof(int)*n2);
        for(i = 0; i < n1; i++) L[i] = A[l+i];
        for(i = 0; i < n2; i++) R[i] = A[m+i+1];

        i = l;

        while(n1 && n2) {
            if(L[0] <= R[0]) {
                A[i] = L[0];
                L++; n1--;
            } else {
                A[i] = R[0];
                R++; n2--;
            }
            i++;
        }
        if(n1) { /* n1 still has items */
            while(n1) {
                A[i] = L[0];
                L++; i++; n1--;
            }
        } else if(n2) { /* n1 still has items */
            while(n2) {
                A[i] = R[0];
                R++; i++; n2--;
            }
        }
    }
    void mergesort_helper(int A[], int l, int r) {
        if(l < r) {
            int m = (l+r)/2;
            mergesort_helper(A, l, m);
            mergesort_helper(A, m+1, r);
            merge(A, l, m, r);
        }
    }
    mergesort_helper(A, 0, n);
    return A;
}

int* quick_sort(int A[], int n) {
    int partition(int A[], int l, int h) {
        int pivot = A[(l+h)/2]; /* take the middle element to be the pivot */
        while(1) {
            while(A[l] < pivot) l++;
            while(A[h] > pivot) h--;
            if(l >= h) return h;
            swap(&A[l], &A[h]);
            l++; h--;
        }
    }
    int* qsort(int A[], int l, int h) {
        if(l < h) {
            int p = partition(A, l, h);
            qsort(A, l, p); /* sort below the pivot */
            qsort(A, p+1, h); /* sort above the pivot */
        }
        return A;
    }
    return qsort(A, 0, n-1);
}

int main(void) {
    int arr[] = {26, 33, 19, 17, 24, 88, 104, -65, 13, -11, 12, 19, 99, -123, 140};
    int n = sizeof(arr) / sizeof(*arr);
    printf("[ - ] Input Array: "); print_arr(arr, n);
    printf("[ * ] Insertion Sort: "); print_arr(insertion_sort(copy_array(arr, n), n), n);
    printf("[ * ] Bubble Sort: "); print_arr(bubble_sort(copy_array(arr, n), n), n);
    printf("[ * ] Selection Sort: "); print_arr(selection_sort(copy_array(arr, n), n), n);
    printf("[ * ] Merge Sort: "); print_arr(merge_sort(copy_array(arr, n), n), n);
    printf("[ * ] Quick Sort: "); print_arr(quick_sort(copy_array(arr, n), n), n);
    return 0;
}

void print_arr(int A[], int n) {
    printf("[");
    for(int i = 0; i < n-1; i++) {
        printf("%d, ", A[i]);
    }
    printf("%d]\n", A[n-1]);
}

int* copy_array(int A[], int n) {
    int* B = (int*)malloc(n * sizeof(int));
    assert(B != NULL);
    for(int i = 0; i < n; i++) {
        B[i] = A[i];
    }
    return B;
}
