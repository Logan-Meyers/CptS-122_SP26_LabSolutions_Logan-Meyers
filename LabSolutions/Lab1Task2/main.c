/*
- Programmer: Logan Meyers
- Class: CptS 122 Lab #11
- Assignment: Lab 1 Task 2
- Date: 01/22/2026
- Decription: String manipulation!
*/

#include "funcs.h"

void testConcat() {
    char dest[10] = "abc";
    char* src = "defgh";

    printf("-- TASK 2A (Concatenation) --\n");
    printf("Dest: %s\nSrc: %s\n", dest, src);
    my_strcat(dest, src);
    printf("After: %s\n", dest);
}

void testReverse() {
    printf("\n-- TASK 2B (Reversing) --\n");
    char rev[20] = "Hello World!";
    printf("Before: %s\n", rev);
    reverseString(rev, strlen(rev));
    printf("After: %s\n", rev);
}
void testStrTok() {
    char line[50] = "We are in CptS 122-42,53;64,90-32;15";
    
    printf("\n-- TASK 2C (custom strtok) --\n");
    printf("Line: %s", line);
    printf("Calling strtok with delimiters: [space] - , ;\n");

    char *ptr = my_strtok(line, " -,;");

    for (; ptr != NULL; ptr = my_strtok(NULL, " -,;")) {
        printf("token: %s\n", ptr);
    }
}

void testMerges() {
    const char str1[50] = "Hello, this is my first string! 24563874986";
    const char str2[50] = "And this is my second! 234672741578";
    char dest[100];

    mergeFixed(str1, str2, dest, sizeof(dest));
    
    printf("\n-- TASK 2D - Merge with Fixed Third Array --\n");
    printf("Str 1: \"%s\"\n", str1);
    printf("Str 2: \"%s\"\n", str2);
    printf("Dest: \"%s\"\n", dest);

    //char *dest2 = NULL;
    //int dest2size = 0;
    //mergeDynamic(str1, str2, &dest2, &dest2size);

    //printf("\n-- TASK 2D - Merge with Dynamic Third Array --\n");
    //printf("Dest: \"%s\"\n", dest2);

    //free(dest2);

    char *dest2 = NULL;
    int dest2size = 0;

    mergeDynamicBetter(str1, str2, &dest2, &dest2size);

    printf("\n-- TASK 2D - Merge with Dynamic Third Array --\n");
    printf("Dest: \"%s\"\n", dest2);

    if (dest2) free(dest2);
}

int main() {
    testConcat();
    testReverse();
    testStrTok();
    testMerges();

    return 0;
}