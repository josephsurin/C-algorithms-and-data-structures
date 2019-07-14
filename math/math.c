#include <stdio.h>

int gcd(int a, int b) {
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(void) {
    int a = 1071, b = 462;
    printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    return 0;
}
