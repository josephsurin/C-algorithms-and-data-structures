# Sorting Algorithms

- [Euclidean Algorithm](#euclidean-algorithm)

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
