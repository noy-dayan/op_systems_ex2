#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* encode(char* str) {
    int len = strlen(str);
    char* encoded = (char*) malloc(len + 1);
    for (int i = 0; i < len; i++) {
        if (islower(str[i]))
            encoded[i] = toupper(str[i]);
        else if (isupper(str[i]))
            encoded[i] = tolower(str[i]);
        else
            encoded[i] = str[i];
    }
    encoded[len] = '\0';
    return encoded;
}

char* decode(char* str) {
    return encode(str); // codecA is reversible, encoding and decoding are the same operation
}
