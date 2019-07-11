#include <stdio.h>

void print_arr(int*, int);

int linear_search(int A[], int n, int x) {
    for(int i = 0; i < n; i++) {
        if(A[i] == x) {
            return i;
        }
    }
    return -1;
}

int binary_search(int A[], int n, int x) {
    int l = 0, h = n;
    while(l < h) {
        int m = (l+h)/2;
        if(A[m] > x) {
            h = m;
        } else if(A[m] < x) {
            l = m+1;
        } else {
            return m;
        }
    }
    return -1;
}

int main(void) {
    int x = 19;

    int arr[] = {7, -3, 0, -3, 9, 19, 46, 11};
    int N = sizeof(arr) / sizeof(*arr);
    printf("[ - ] Input Array 1: "); print_arr(arr, N); 
    printf("[ * ] Linear Search on Array 1: %d is at index %d\n", x, linear_search(arr, N, x)); 

    int x2 = 1;
    int arr2[] = {-33, -19, -2, -1, 0, 0, 1, 4, 5, 9, 16, 18, 19, 23, 44, 47};
    int N2 = sizeof(arr2) / sizeof(*arr2);
    printf("[ - ] Input Array 2: "); print_arr(arr2, N2);
    printf("[ * ] Binary Search on Array 2: %d is at index %d\n", x2, binary_search(arr2, N2, x2));
}

void print_arr(int A[], int n) {
    printf("[");
    for(int i = 0; i < n-1; i++) {
        printf("%d, ", A[i]);
    }
    printf("%d]\n", A[n-1]);
}
