#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

int copy_file(const char *src, const char *dst, int force, int verbose) {
    FILE *src_file, *dst_file;
    char buf[BUF_SIZE];
    size_t nread;
    
    if (!src || !dst) {
        fprintf(stderr, "Usage: copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }
    
    // try access the source file for reading
    src_file = fopen(src, "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error opening source file %s: %s\n", src, strerror(errno));
        return 1;
    }
    
    // check if the destination file exists
    dst_file = fopen(dst, "rb");
    if (dst_file != NULL) {
        fclose(dst_file);
        if (!force) {
            fprintf(stderr, "Target file %s already exists. Use -f to force overwrite.\n", dst);
            fclose(src_file);
            return 1;
        }
    }
    
    // try access the destination file for writing
    dst_file = fopen(dst, "wb");
    if (dst_file == NULL) {
        fprintf(stderr, "Error opening destination file %s: %s\n", dst, strerror(errno));
        fclose(src_file);
        return 1;
    }

    // copy the contents of the source file to the destination file
    int result = 0;
    while ((nread = fread(buf, 1, BUF_SIZE, src_file)) > 0) {
        if (fwrite(buf, 1, nread, dst_file) != nread) {
            fprintf(stderr, "Error writing to destination file %s: %s\n", dst, strerror(errno));
            result = 1;
            break;
        }
    }
    
    // close file pointers
    fclose(src_file);
    fclose(dst_file);
    
    // print verbose output if requested
    if (verbose) {
        if (result == 0) {
            printf("Success\n");
        } else if (errno == EEXIST) {
            printf("Target file exists\n");
        } else {
            printf("General failure\n");
        }
    }
    
    // return the result
    return result;
}

int main(int argc, char *argv[]) {
    int force = 0, verbose = 0;
    char *src_file, *dst_file;
    
    if (argc < 3) {
        fprintf(stderr, "Usage: ./copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }

    // read args
    src_file = argv[1];
    dst_file = argv[2];
    
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            force = 1;
        }
    }
    
    return copy_file(src_file, dst_file, force, verbose);
}
