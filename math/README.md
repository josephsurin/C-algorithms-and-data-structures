# Math Algorithms

- [Euclidean Algorithm](#euclidean-algorithm)
- [Least Common Multiple](#least-common-multiple)
- [Extended Euclidean Algorithm](#extended-euclidean-algorithm)
- [Exponentiation](#exponentiation)
- [Modular Exponentiation](#modular-exponentiation)

## Euclidean Algorithm <a name="euclidean-algorithm"></a>

Calculates the [gcd](https://en.wikipedia.org/wiki/Greatest_common_divisor) of two numbers, by using the sequence defined by `r(n) = r(n-2) % r(n-1)` with `r(0) = a` and `r(1) = b`. The gcd is given by `r(k-1)` where `r(k) == 0`.

#### Implementation:

```C
int gcd(int a, int b) {
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
```

## Least Common Multiple <a name="least-common-multiple"></a>

Calculates the [lcm](https://en.wikipedia.org/wiki/Least_common_multiple) of two numbers, using the fact that `lcm(a, b) = |ab|/gcd(a, b)`.

#### Implementation

```C
int lcm(int a, int b) {
    return abs(a*b)/gcd(a, b);
}
```

## Extended Euclidean Algorithm <a name="extended-euclidean-algorithm"></a>

Calculates the gcd and the (minimal) [Bézout coefficients](https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity) of two numbers. The procedure for the extended euclidean algorithm resembles that of the euclidean algorithm, except that two extra sequences are produced. If the sequence `q(n)` represents the quotients at each step, then `r(n+1) = r(n-1) - q(n)r(n)` with `r(0) = a` and `r(1) = b`. The two additional sequences `s(n)` and `t(n)` determine the Bézout coefficients. Namely, when `r(k) == 0`, the gcd is given by `r(k-1)`, and the Bézout coefficients are given by `s(k-1)` and `t(k-1)`. `s(n)` and `t(n)` are recursively defined as follows: `s(n+1) = s(n-1) - q(n)s(n), s(0) = 1, s(1) = 0`, `t(n+1) = t(n-1) - q(n)t(n), t(0) = 0, t(1) = 1`.

#### Implementation:

```C
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
```

## Exponentiation <a name="exponentiation"></a>

Calculates the value of `a^b`. This algorithm takes advantage of the fact that `a^b == (a^(b/2))^2` for even values of `b`.

#### Implemenetation:

```C
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
```

## Modular Exponentiation <a name="modular-exponentiation"></a>

Calculates the value of `b^e mod n`. This algorithm takes advantage of the fact that the exponent `e` can be expressed as a sum of powers of two (i.e. `e = sum from i=0 to n-1 of a_i * 2^i` where `a_i` is the `i+1`th most significant bit of `e`. For example, if `e = 10`, then `a_0 = 0, a_1 = 1, a_2 = 0, a_3 = 1`). From this, we can write the expression `b^e` as `b^(a_0*2^0 + a_1*2^1 + a_2*2^2 ... + a_(n-1)*2^(n-1)) = product from i=0 to n-1 of (b^(2^i))^a_i`. Therefore, the quantity `b^e mod n` is equal to `product from i=0 to n-1 of (b^(2^i))^a_i mod n`.

$$e = \sum_{i=0}^{n-1} a_i2^i$$
$$ b^e = b^{a_0 2^0 + a_1 2^1 + a_2 2^2 + \dots + a_{n-1} 2^{n-1}}$$
$$b^e \mod n = \prod_{i=0}^{n-1} [(b^{2^i})^{a_i} \mod n]$$

#### Implementation:

```C
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
```
