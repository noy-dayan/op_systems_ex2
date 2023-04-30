#include <stdio.h>
#include <stdlib.h>
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

    // look up the decode function
    char* (*decode)(char*);
    *(void **)(&decode) = dlsym(handle, "decode");
    if (!decode) {
        printf("Error looking up function: %s\n", dlerror());
        return 1;
    }

    // call the decode function and print the result
    char* decoded = decode(message);
    printf("%s\n", decoded);

    // clean up
    free(decoded);
    dlclose(handle);

    return 0;
}
