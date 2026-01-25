/*
- Programmer: Logan Meyers
- Class: CptS 122 Lab #11
- Assignment: Lab 1 Task 2
- Date: 01/22/2026

- File: funcs.c
- Description: file definitions for all functions declared in funcs.h
*/

#include "funcs.h"

char *my_strcat(char *destination, const char *source) {
    // create our working variables
    int dest_len = strlen(destination);  // length of destination
    int src_len = strlen(source);  // length of source

    // loop through source characters from beginning to end
    for (int i = 0; i < src_len; i++) {
        // put in character from source to dest
        destination[dest_len + i] = source[i];
    }

    // add final null char to end string
    destination[dest_len+strlen(source)] = '\0';

    // return dest. pointer we were given
    return destination;
}

void reverseString(char *str, int len) {
    // base case
    if (len <= 1) return;

    // swap characters
    char tmp = str[0];
    str[0] = str[len-1];
    str[len-1] = tmp;

    // recursive call
    reverseString(str+1, len-2);
}

int char_in_str(char c, char *str) {
    for (int i=0; i < strlen(str); i++) {
        if (c == str[i]) return 1;
    }
    return 0;
}

char *my_strtok(char *str, const char *delim) {
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

void mergeFixed(const char* str1, const char* str2, char* dest, const int dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return;

    // base check: have to have a destination
    if (dest == NULL)
        return;
    
    // create an array to hold counts of all ascii values found (frequency table)
    unsigned int counts[256] = {0};
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
    for (int i = 0; i < 256 && destidx < dest_size-1; i++) {
        while (counts[i]) {
            dest[destidx] = (char)i;
            destidx++;
            counts[i]--;
        }
    }

    dest[destidx] = '\0';
}

void mergeDynamic(const char* str1, const char* str2, char** dest, int* dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return;

    // base check: have to have a dest_size pointer given
    if (dest_size == NULL)
        return;

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

        *dest = malloc(*dest_size*sizeof(char));
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

                return;
            }
            *dest = (char *)ret;
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
}

void mergeDynamicBetter(const char* str1, const char* str2, char** dest, int* dest_size) {
    // base check: have to have at least one string with values
    if (str1 == NULL && str2 == NULL)
        return;

    // base check: have to have a dest_size pointer given
    if (dest_size == NULL)
        return;

    // get the size we'll need
    size_t size_needed = 1;  // 1 for null char at end
    if (str1) size_needed += strlen(str1);
    if (str2) size_needed += strlen(str2);
    
    // malloc or realloc memory for dest
    void *ret = NULL;
    if (*dest == NULL)
        ret = malloc((size_t)(size_needed * sizeof(char)));
    else {
        ret = realloc(*dest, (size_t)(size_needed * sizeof(char)));
    }

    if (ret == NULL) {
        printf("!! realloc/malloc failed");
        return;
    }
       
    *dest = (char *)ret;
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
    for (int i = 0; i < 256 && i < *dest_size-1; i++) {
        while (counts[i]) {
            (*dest)[destidx] = (char)i;
            destidx++;
            counts[i]--;
        }
    }

    (*dest)[destidx] = '\0';
}
