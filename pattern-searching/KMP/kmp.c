#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int* failure_function(char* P) {
    int m = strlen(P);
    int* F = malloc(sizeof(int) * m);
    F[0] = -1;
    if(m == 1) return F;
    F[1] = 0;
    int s = 2;
    int c = 0;
    while(s < m) {
        if(P[c] == P[s-1]) {
            F[s] = c++;
            s++;
        } else if(c > 0) {
            c = F[c];
        } else {
            F[s] = 0;
            s++;
        }
    }
    return F;
}

int kmp_search(char* text, char* P) {
    int* F = failure_function(P);
    int n = strlen(text);
    int m = strlen(P);
    int s = 0;
    int i = 0;
    while(s <= n - m) {
        while(text[s + i] == P[i]) i++;
        if(i == m) return s;
        s += i - F[i];
        i = MAX(F[i], 0);
    }
    return -1;
}

int main(void) {
    char* text = "hello i am a test string!";
    char* pattern = "i am a";
    int match = kmp_search(text, pattern);
    printf("'%s' is in '%s' at position %d\n", pattern, text, match);
    return 0;
}
