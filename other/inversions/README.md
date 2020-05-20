# Inversions

Let `A[0..n-1]` be an array of `n` distinct numbers. If `i < j` and `A[i] > A[j]`, then we call `(i, j)` an inversion.

e.g. `A = [3, 1, 2]` has the two inversions `(3, 1)`, `(3, 2)`.

- [Counting Inversions](#counting-inversions)

## Counting Inversions <a name="counting-inversions"></a>

The naive approach would be to check elements pairwise, resulting in `O(n^2)` average case. We can use a divide and conquer method to reduce the time complexity to `O(nlogn)` worst case. We use an approach similar to merge sort and the fact that a sorted array trivially has no inversions.

We make use of a helper "merge" function which returns the count of inversions within the range of elements specified by the inputs. The merge function takes the array input `A`, and three integers `l`, `m` and `h` which represent the bounds for the lower and upper sections to be merged: `L[l..m]` and `U[m..h]`. `L` and `U` are assumed to be sorted. We initialise a counter variable `c` to count the number of inversions in `A[l..h]`. We also initialise two variables `j = l` and `k = m` to keep track of the position within `L` and `U` respectively. We then proceed with a loop that, at each step, does the following: If `L[j] < U[k]`, then set `A[l] = L[j]` and increment both `j` and `l`. Otherwise, we have `U[k] <= L[j]` and so `U[k]` belongs in `A[l]`. Additionally, this tells us that all of the remaining elements to be considered in `L` are larger than `U[k]`, and so we increment `c` by `m-l-j`. We also increment both `k` and `l`.

The main function will involve recursive calls to itself and a call to the merge function as per usual merge sort. The function takes the array input `A` and two integers `l` and `h` which represent the region of the array for which to count inversions for. If `l < h`, we let `m = floor[(l+h)/2]` and initialise a counter variable `c = 0`. We then recursively call ourselves with arguments `(A, l, m)` and `(A, m, h)`. We then merge the results with arguments `(A, l, m, h)`. Summing the return values of these three function calls in the variable `c` and then finally returning `c` gives the total number of inversions in the array.

#### Implementation:

```C
#include <stdlib.h>

int merge_count(int A[], int l, int m, int h) {
    int* L = (int*)calloc(m-l, sizeof(int));
    int* U = (int*)calloc(h-m, sizeof(int));
    int i = l, ii = 0;
    while(i < m) {
        L[ii++] = A[i++];
    }
    ii = 0;
    while(i < h) {
        U[ii++] = A[i++];
    }
    int ll = l;
    int j = 0, k = 0, c = 0;
    while(j < m-ll && k < h-m) {
        if(L[j] < U[k]) {
            A[l++] = L[j++];
        } else {
            c += m - ll - j;
            A[l++] = U[k++];
        }
    }
    if(j == m-ll) { /* L is empty */
        while(l < h && k < h-m) {
            A[l++] = U[k++];
        }
    } else { /* U is empty */
        while(l < h && j < m-ll) {
            A[l++] = L[j++];
        }
    }
    return c;
}

int count_inversions(int A[], int l, int h) {
    int c = 0;
    if(l+1 < h) {
        int m = (l+h)/2;
        c += count_inversions(A, l, m);
        c += count_inversions(A, m, h);
        c += merge_count(A, l, m, h);
    }
    return c;
}
```
