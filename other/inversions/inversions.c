#include <stdio.h>
#include <stdlib.h>

void print_arr(int A[], int n);

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

void print_arr(int A[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d, ", A[i]);
    }
}

int main(int argc, char* argv[]) {
    int A[148] = { 11778,6147,4100,11783,11790,5652,7190,539,10271,8735,6177,5669,7209,553,4654,1077,8763,11329,1602,8259,7238,70,11849,4687,2129,5206,9303,2136,8281,6746,609,4706,4194,6769,5751,121,3197,1150,3203,4228,8849,7313,9364,11415,7834,10398,1187,3754,7342,8372,9401,4806,5831,2762,5834,1237,726,4823,3287,9433,3804,732,8417,7395,3303,8425,3308,9452,4847,4848,10995,11509,12025,4346,8443,3328,11524,7941,777,268,7949,2325,11030,4386,2853,5928,4904,9007,7472,5424,1846,11066,7483,8005,6472,8529,2386,4435,6997,9048,1369,11108,7012,8038,7526,3437,9587,6004,12154,3452,1407,7551,6019,11654,8074,3467,1932,12174,1425,10648,2461,7591,11688,6057,5544,2475,3499,8633,11197,957,11207,12233,12235,6607,8143,9172,5084,10718,6622,4067,11239,6637,8685,6638,10226,10740,9717,3065 };
    printf("inversions: %d\n", count_inversions(A, 0, 148));
    print_arr(A, 148);
    return 0;
}
