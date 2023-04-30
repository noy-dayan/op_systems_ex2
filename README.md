
# cmp.c
cmp.c is a simple C program that compares the contents of two files and determines whether they are equal or distinct. The program takes two file names as input arguments and can also be optionally configured to perform case-insensitive comparison and print verbose output.

## Usage:
    ./cmp <file1> <file2> [-v] [-i]

## Arguments:
<file1> - The path to the first file to be compared.
<file2> - The path to the second file to be compared.
[-v] - Optional flag that enables verbose output. If this flag is set, the program will print "equal" or "distinct" depending on whether the files are equal or distinct.
[-i] - Optional flag that enables case-insensitive comparison. If this flag is set, the program will perform comparison in a case-insensitive manner.

## Return values:
0 - The contents of the two files are equal.
1 - The contents of the two files are distinct.
2 - Invalid or insufficient arguments were passed to the program.

## Examples:

Compare two files "file1.txt" and "file2.txt" and returns the result:
    ./cmp file1.txt file2.txt

Compare two files "file1.txt" and "file2.txt" in case-insensitive mode and returns the result:
    ./cmp file1.txt file2.txt -i

Compare two files "file1.txt" and "file2.txt" ,returns the result and print verbose output:
    ./cmp file1.txt file2.txt -v

Compare two files "file1.txt" and "file2.txt" in case-insensitive mode ,returns the result and print verbose output:
    ./cmp file1.txt file2.txt -v -i
    ./cmp file1.txt file2.txt -i -v
