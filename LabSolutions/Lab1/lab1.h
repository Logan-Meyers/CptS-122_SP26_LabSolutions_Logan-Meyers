#pragma once

#ifndef LAB1_H
#define LAB1_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------ TASK 1 ------------------------------ */

/// <summary>
/// Demo task 1
/// </summary>
void task1();

/* ------------------------------ TASK 2 ------------------------------ */

/// <summary>
/// Demo task 2
/// </summary>
void task2();

/// <summary>
/// Demo custom strcat function
/// </summary>
void testConcat();

/// <summary>
/// Demo custom string reverse function
/// </summary>
void testReverse();

/// <summary>
/// Demo custom strtok function
/// </summary>
void testStrTok();

/// <summary>
/// Test custom string merging functions
/// </summary>
void testMerges();

/// <summary>
/// Custom strcat implementation, concatenates two strings
/// </summary>
/// <param name="destination">c string (char array) to concatenate onto</param>
/// <param name="source">c string to concatenate onto destination</param>
/// <returns>destination c string</returns>
char* my_strcat(char* destination, const char* source);

/// <summary>
/// Reverse a string recursiely
/// </summary>
/// <param name="str">c string to reverse</param>
/// <param name="len">length of string</param>
void reverseString(char* str, int len);

/// <summary>
/// Helper for my_strtok, checks if the given character is in a given string
/// </summary>
/// <param name="c">char to check</param>
/// <param name="str">c string of acceptable characters</param>
/// <returns>1 (true) or 2 (false)</returns>
int char_in_str(char c, char* str);

/// <summary>
/// My custom implementation of strtok
/// </summary>
/// <param name="str">character array to parse and tokenize</param>
/// <param name="delim">c string of acceptable delimiters</param>
/// <returns>char array pointer to next found token</returns>
char* my_strtok(char* str, const char* delim);

/// <summary>
/// My custom merge function using a fixed-size array. Will truncate merge if destination is not big enough/
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">Destination array to merge into</param>
/// <param name="dest_size">Size of the destination array, will not change</param>
/// <returns>Pointer to merged string</returns>
char* mergeFixed(const char* str1, const char* str2, char* dest, const int dest_size);

/// <summary>
/// My custom merge function using a dynamically-resized array.
/// Sometimes causes a runtime error, not sure why.
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">pointer to destination array pointer</param>
/// <param name="dest_size">pointer to size of destination array</param>
/// <returns>Pointer to merged string</returns>
char* mergeDynamic(const char* str1, const char* str2, char** dest, int* dest_size);

/// <summary>
/// My custom merge function using a dynamically-resized array.
/// Causes errors much less, by creating an array one time with enough space.
/// This is the way I'd recommend doing it, one-and-done.
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">pointer to destination array pointer</param>
/// <param name="dest_size">pointer to size of destination array</param>
/// <returns>Pointer to merged string</returns>
char* mergeDynamicBetter(const char* str1, const char* str2, char** dest, int* dest_size);

/// <summary>
/// Function to compare two characters. Needed for qsort in mergeToDest.
/// </summary>
/// <param name="a">First character</param>
/// <param name="b">Second character</param>
/// <returns></returns>
int cmp_char(const void* a, const void* b);

/// <summary>
/// My custom merge function without a third array. Works by concatenating onto dest, then sorting.
/// </summary>
/// <remark>This uses C's built in <c>qsort</c>, but you could implement your own algorithm if you wanted.</remark>
/// <param name="dest">Destination array</param>
/// <param name="source">Source array</param>
/// <param name="dest_size">Space allocated for destination array</param>
/// <returns>Pointer to merged string</returns>
/// 
char* mergeToDest(char* dest, const char* source, int dest_size);

#endif