#include <stdio.h>

int gcd(int a, int b) {
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int xgcd(int a, int b, int* s, int* t) {
    int s0 = 1, s1 = 0;
    int t0 = 0, t1 = 1;
    int r, q, temp;
    while(b != 0) {
        r = a % b;
        q = a / b;
        temp = s1;
        s1 = s0 - q*s1;
        s0 = temp;
        temp = t1;
        t1 = t0 - q*t1;
        t0 = temp;
        a = b;
        b = r;
    }
    *s = s0;
    *t = t0;
    return a;
}

int pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res *= a;
            b--;
        }
        a *= a;
        b /= 2;
    }
    return res;
}

int pow_mod(int b, int e, int n) {
    if(n == 1) return 0;
    int res = 1;
    b = b % n;
    while(e) {
        if(e & 1) {
            res = (res * b) % n;
        }
        e = e >> 1;
        b = (b * b) % n;
    }
    return res;
}

int main(void) {
    int a = 1071, b = 462;
    printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    int x, y;
    int g = xgcd(a, b, &x, &y);
    printf("xgcd: %d*%d + %d*%d = %d\n", x, a, y, b, g);
    int c = 8, d = 7;
    printf("pow(%d, %d) = %d\n", c, d, pow(c, d));
    printf("pow_mod(%d, %d, %d) = %d\n", a, c, b, pow_mod(a, c, b));
    return 0;
}
