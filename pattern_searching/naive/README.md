# Naive Pattern Search

Given a pattern of length `m` and a text of length `n` with `n >= m`, for each character in the text, compare up to `m` characters starting at that character with the pattern to see whether there is a match or not.

##### Implementation:

```C
int naive(char* text, char* pattern) {
    int i = 0;
    int j, k;
    while(text[i]) {
        j = i;
        k = 0;
        while(text[j++] == pattern[k++] && pattern[k] != '\0');
        if(text[j] == '\0' && pattern[k] != '\0') {
            return -1;
        }
        if(pattern[k] == '\0') {
            return i;
        }
        i++;
    }
    return -1;
}
```
