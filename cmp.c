#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int verbose = 0;
    int ignore_case = 0;
    char *file1, *file2;
    FILE *fp1, *fp2;
    int c1, c2, result;

    if (argc < 3) {
        fprintf(stderr, "Usage: ./cmp <file1> <file2> [-v] [-i]\n");
        return 2;
    }

    // read args
    file1 = argv[1];
    file2 = argv[2];

    if (argc > 3) {
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "-v") == 0) {
                verbose = 1;
            } else if (strcmp(argv[i], "-i") == 0) {
                ignore_case = 1;
            } else {
                fprintf(stderr, "Unknown option: %s\n", argv[i]);
                return 2;
            }
        }
    }

    // try access first file
    fp1 = fopen(file1, "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", file1);
        return 1;
    }

    // try access second file
    fp2 = fopen(file2, "r");
    if (fp2 == NULL) {
        fclose(fp1);
        fprintf(stderr, "Error: cannot open file %s\n", file2);
        return 1;
    }

    result = 0;
    // read from files and compare
    while (1) {
        c1 = fgetc(fp1);
        c2 = fgetc(fp2);

        if (ignore_case) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }

        if (c1 != c2) {
            result = 1;
            break;
        }

        if (c1 == EOF || c2 == EOF) {
            break;
        }
    }

    // close file pointers
    fclose(fp1);
    fclose(fp2);

    // print verbose output if requested
    if (verbose) {
        if (result == 0) {
            printf("equal\n");
        } else {
            printf("distinct\n");
        }
    }

    // return the result
    return result;
}
