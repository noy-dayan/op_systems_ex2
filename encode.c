#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    // read args
    char* codec_name = argv[1];
    char* message = argv[2];

    // load the shared library
    void* handle = dlopen(codec_name, RTLD_LAZY);
    if (!handle) {
        printf("Error loading library: %s\n", dlerror());
        return 1;
    }

    // look up the encode function
    char* (*encode)(char*);
    *(void **)(&encode) = dlsym(handle, "encode");
    if (!encode) {
        printf("Error looking up function: %s\n", dlerror());
        return 1;
    }

    // call the encode function and print the result
    char* encoded = encode(message);
    printf("%s\n", encoded);

    // clean up
    free(encoded);
    dlclose(handle);

    return 0;
}
