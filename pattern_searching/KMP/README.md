# KMP Pattern Search

Similar to naive pattern search, except we use an auxilliary data structure (called the failure function and denoted by `F`) which is an array of the same size as the pattern. We define `F[i]` to be the maximum value `k` such that `k < i` and `P[0...k-1]` matches `P[i-k...i-1]` (where `P` is the pattern), and we defined `F[0] = -1`. In other words, `F[i]` is the length of the longest prefix of the pattern that matches a suffix of the characters in the pattern that come before the character at index `i`.

e.g.

`P = "abcd#abce"`

```
i     0  1  2  3  4  5  6  7  8
P     a  b  c  d  #  a  b  c  e
F[i]  -1 0  0  0  0  0  1  2  3
```

For `i = 7` for example, `P[0..1] = "ab"` matches `P[5..6] = "ab"`.
This array can be constructed in linear time.

The array is used to help us "backtrack" so we don't miss a match. In order to improve efficiency over naive pattern search, we can jump ahead by a certain amount once we found a mismatch between the pattern and the text. So when we find a mismatch, we jump ahead as far as possible without moving past any matching prefix of the pattern.

e.g.

`P = "aba", T = "ab#abd#aba"`

```
i     0  1  2
P     a  b  a
F[i]  -1 0  1
```

The row second from the bottom represents the pattern and where we are comparing it against.
`*` in the bottom row represents a match, and `X` represents a mismatch.

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
      a  b  a
      *  *  X
```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
         a  b  a
         X
```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
            a  b  a
            X
```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
               a  b  a
               *  *  X

```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
                  a  b  a
                  X

```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
                     a  b  a
                     X

```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
                        a  b  a
                        X

```

```
i     0  1  2  3  4  5  6  7  8  9
T     a  b  #  a  b  d  #  a  b  a
                           a  b  a
                           *  *  *

```

Essentially, we loop through with a variable `s` which points to the index that we are starting to compare the text against the pattern. When we check for matches, we use the variable `i` to keep track of how many characters matched. If `i` ends up being the length of the pattern, we have found a match, if not, then we move `s` forward by `i`, however, we need to account for the possibility of part of the pattern appearing in the text in the part we just skipped over, so we shift back by `F[i]` to ensure we do not miss any matches. We then reset `i` to be the larger of `0` or `F[i]` (since we already know it will match the first `F[i]` characters at its new position)

We construct `F` using similar logic:

First, set `F[0] = -1` and `F[1] = 0`. Then, we use two variables `c` and `s` to examine and compare the prefix and suffix of the string `P[0..i-1]`. To begin, we set `s = 2` and `c = 0` (`s` is 2 since we have already cleared the first two characters). Then we continue with the loop invariant being `s < m`. If `P[c] == P[s-1]` (that is, if the prefix is matching the suffix), then we set `F[s] = c = 1` and increment both `c` and `s`. Otherwise, if `c > 0` (that is, we just stopped having a matching prefix and suffix), then set `c = F[c]`. Otherwise, we do not have any matches in the prefix and suffix, so we set `F[s] = 0` and increment `s`.

##### Implementation:
