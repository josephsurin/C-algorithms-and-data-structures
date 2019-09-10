#include <stdio.h>

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

int main(void) {
    char* text = "hello i am a test string!";
    char* pattern = " i am a";
    int match = naive(text, pattern);
    printf("%s is in %s at position %d\n", pattern, text, match);
    return 0;
}
