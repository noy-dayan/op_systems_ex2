#include <string.h>
#include <stdlib.h>

char* encode(char* str) {
    int len = strlen(str);
    char* encoded = (char*) malloc(len + 1);
    for (int i = 0; i < len; i++) {
        encoded[i] = str[i] + 3;
    }
    encoded[len] = '\0';
    return encoded;
}

char* decode(char* str) {
    int len = strlen(str);
    char* decoded = (char*) malloc(len + 1);
    for (int i = 0; i < len; i++) {
        decoded[i] = str[i] - 3;
    }
    decoded[len] = '\0';
    return decoded;
}
