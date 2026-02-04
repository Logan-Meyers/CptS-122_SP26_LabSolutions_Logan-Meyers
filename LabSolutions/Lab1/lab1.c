#include "lab1.h"

/* ------------------------------ TASK 1 ------------------------------ */

void task1() {
    printf("Hello world! I'm in CptS 122!!\n");
}

/* ------------------------------ TASK 2 ------------------------------ */

void task2() {
    testConcat();
    testReverse();
    testStrTok();
    testMerges();
}

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

    char* ptr = my_strtok(line, " -,;");

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

    /* ----- code for the original dynamic merge ----- */
    //char *dest2 = NULL;
    //int dest2size = 0;
    //mergeDynamic(str1, str2, &dest2, &dest2size);

    //printf("\n-- TASK 2D - Merge with Dynamic Third Array --\n");
    //printf("Dest: \"%s\"\n", dest2);

    //free(dest2);

    char* dest2 = NULL;
    int dest2size = 0;

    mergeDynamicBetter(str1, str2, &dest2, &dest2size);

    printf("\n-- TASK 2D - Merge with Dynamic Third Array --\n");
    printf("Dest: \"%s\"\n", dest2);

    if (dest2) free(dest2);

    char dest3[150];
    strcpy(dest3, str1);
    mergeToDest(dest3, str2, sizeof(dest3));

    printf("\n-- TASK 2D - Merge with No Third Array --\n");
    printf("Dest: \"%s\"", dest3);
}

char* my_strcat(char* destination, const char* source) {
    // create our working variables
    int dest_len = strlen(destination);  // length of destination
    int src_len = strlen(source);  // length of source

    // loop through source characters from beginning to end
    for (int i = 0; i < src_len; i++) {
        // put in character from source to dest
        destination[dest_len + i] = source[i];
    }

    // add final null char to end string
    destination[dest_len + strlen(source)] = '\0';

    // return dest. pointer we were given
    return destination;
}

void reverseString(char* str, int len) {
    // base case
    if (len <= 1) return;

    // swap characters
    char tmp = str[0];
    str[0] = str[len - 1];
    str[len - 1] = tmp;

    // recursive call
    reverseString(str + 1, len - 2);
}

int char_in_str(char c, char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (c == str[i]) return 1;
    }
    return 0;
}

char* my_strtok(char* str, const char* delim) {
    static char* pToken;
    char* workingString = NULL;

    // string isn't null, set ptoken
    if (str != NULL) {
        pToken = str;
    }
    // string is null, return null if ptoken null (no more to work through)
    if (pToken == NULL) {
        return NULL;
    }

    // main loop to parse next data
    while (*pToken != '\0') {
        // if working string null, continue finding next non-delim
        if (workingString == NULL) {
            // set working string if non-delim found
            if (!char_in_str(*pToken, delim)) {
                workingString = pToken;
            }
        }
        // else working string set, find next delim
        else {
            if (char_in_str(*pToken, delim)) {
                *pToken = '\0';
                pToken++;
                break;
            }
        }

        // increment along the string
        pToken++;
    }

    // return working string, the token found (or not)
    return workingString;
}

char* mergeFixed(const char* str1, const char* str2, char* dest, const int dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return NULL;

    // base check: have to have a destination
    if (dest == NULL)
        return NULL;

    // create an array to hold counts of all ascii values found (frequency table)
    unsigned int counts[256] = { 0 };
    // make sure filled with zeros
    for (int i = 0; i < 256; i++) {
        counts[i] = 0;
    }

    // count all characters found in str1
    if (str1 != NULL)
        for (int i = 0; i < strlen(str1); i++) {
            counts[(int)str1[i]]++;
        }

    // count all characters found in str2
    if (str2 != NULL)
        for (int i = 0; i < strlen(str2); i++) {
            counts[(int)str2[i]]++;
        }

    // fill dest with characters in order
    int destidx = 0;
    for (int i = 0; i < 256 && destidx < dest_size - 1; i++) {
        while (counts[i]) {
            dest[destidx] = (char)i;
            destidx++;
            counts[i]--;
        }
    }

    dest[destidx] = '\0';

    return dest;
}

char* mergeDynamic(const char* str1, const char* str2, char** dest, int* dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return NULL;

    // base check: have to have a dest_size pointer given
    if (dest_size == NULL)
        return NULL;

    // set dest size to a default
    if (*dest_size == 0)
        *dest_size = 16;

    // allocate memory for dest
    if (*dest == NULL)
        *dest = malloc((size_t)(*dest_size));

    // set an array if no destination array is given
    if (*dest == NULL) {
        // if dest_size is 0, set to a default 16
        if (*dest_size == 0)
            *dest_size = 16;

        *dest = malloc(*dest_size * sizeof(char));
    }

    // create an array to hold counts of all ascii values found (frequency table)
    unsigned int counts[256] = { 0 };

    // count all characters found in str1
    if (str1 != NULL) {
        int str1len = strlen(str1);

        for (int i = 0; i < str1len; i++) {
            counts[(int)str1[i]]++;
        }
    }

    // count all characters found in str2
    if (str2 != NULL) {
        int str2len = strlen(str2);

        for (int i = 0; i < str2len; i++) {
            counts[(int)str2[i]]++;
        }
    }

    // fill dest with characters in order
    int destidx = 0;
    for (int i = 0; i < 256; i++) {
        if (destidx == *dest_size) {
            void* ret = realloc(*dest, ((*dest_size) + 1) * sizeof(char));
            if (ret == NULL) {
                printf("!! realloc failed\n");

                return NULL;
            }
            *dest = (char*)ret;
            (*dest_size)++;
            printf("...Resized to hold %d items\n", *dest_size);
        }

        while (counts[i]) {
            (*dest)[destidx] = (char)i;
            destidx++;
            counts[i]--;
        }
    }

    (*dest)[destidx] = '\0';

    return *dest;
}

char* mergeDynamicBetter(const char* str1, const char* str2, char** dest, int* dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return NULL;

    // base check: have to have a dest_size pointer given
    if (dest_size == NULL)
        return NULL;

    // get the size we'll need
    size_t size_needed = 1;  // 1 for null char at end
    if (str1) size_needed += strlen(str1);
    if (str2) size_needed += strlen(str2);

    // malloc or realloc memory for dest
    void* ret = NULL;
    if (*dest == NULL)
        ret = malloc((size_t)(size_needed * sizeof(char)));
    else {
        ret = realloc(*dest, (size_t)(size_needed * sizeof(char)));
    }

    if (ret == NULL) {
        printf("!! realloc/malloc failed");
        return NULL;
    }

    *dest = (char*)ret;
    *dest_size = (int)size_needed;

    // create an array to hold counts of all ascii values found (frequency table)
    unsigned int counts[256] = { 0 };

    // count all characters found in str1
    if (str1 != NULL) {
        int str1len = strlen(str1);

        for (int i = 0; i < str1len; i++) {
            counts[(int)str1[i]]++;
        }
    }

    // count all characters found in str2
    if (str2 != NULL) {
        int str2len = strlen(str2);

        for (int i = 0; i < str2len; i++) {
            counts[(int)str2[i]]++;
        }
    }

    // fill dest with characters in order
    int destidx = 0;
    for (int i = 0; i < 256 && destidx < *dest_size - 1; i++) {
        while (counts[i]) {
            (*dest)[destidx] = (char)i;
            destidx++;
            counts[i]--;
        }
    }

    (*dest)[destidx] = '\0';

    return *dest;
}

int cmp_char(const void* a, const void* b) {
    unsigned char ca = *(const unsigned char*)a;
    unsigned char cb = *(const unsigned char*)b;
    return (ca > cb) - (ca < cb);
}

char* mergeToDest(char* dest, const char* source, int dest_size) {
    int dest_len = 0, source_len = 0;

    /* find end of dest, but not beyond dest_size */
    while (dest_len < dest_size && dest[dest_len]) dest_len++;
    if (dest_len == dest_size) { /* no NUL found — unsafe state; do nothing */
        return dest;
    }

    /* append as much of src as fits (leave room for NUL) */
    while (dest_len + 1 < dest_size && source[source_len]) {
        dest[dest_len++] = source[source_len++];
    }
    dest[dest_len] = '\0';

    /* sort characters in-place (only the visible part, excluding NUL) */
    if (dest_len > 1) {
        qsort(dest, dest_len, sizeof(char), cmp_char);
    }

    return dest;
}