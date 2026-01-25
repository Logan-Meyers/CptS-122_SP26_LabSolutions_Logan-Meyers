/*
- Programmer: Logan Meyers
- Class: CptS 122 Lab #11
- Assignment: Lab 1 Task 2
- Date: 01/22/2026

- File: funcs.h
- Description: function declarations for all helper functions for
			   lab1task2
*/

#ifndef LAB1_H
#define LAB1_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// <summary>
/// Custom strcat implementation, concatenates two strings
/// </summary>
/// <param name="destination">c string (char array) to concatenate onto</param>
/// <param name="source">c string to concatenate onto destination</param>
/// <returns>destination c string</returns>
char *my_strcat(char *destination, const char *source);

/// <summary>
/// Reverse a string recursiely
/// </summary>
/// <param name="str">c string to reverse</param>
/// <param name="len">length of string</param>
void reverseString(char *str, int len);

/// <summary>
/// Helper for my_strtok, checks if the given character is in a given string
/// </summary>
/// <param name="c">char to check</param>
/// <param name="str">c string of acceptable characters</param>
/// <returns>1 (true) or 2 (false)</returns>
int char_in_str(char c, char *str);

/// <summary>
/// My custom implementation of strtok
/// </summary>
/// <param name="str">character array to parse and tokenize</param>
/// <param name="delim">c string of acceptable delimiters</param>
/// <returns>char array pointer to next found token</returns>
char *my_strtok(char *str, const char *delim);

/// <summary>
/// My custom merge function using a fixed-size array. Will truncate merge if destination is not big enough/
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">Destination array to merge into</param>
/// <param name="dest_size">Size of the destination array, will not change</param>
void mergeFixed(const char *str1, const char *str2, char *dest, const int dest_size);

/// <summary>
/// My custom merge function using a dynamically-resized array.
/// Sometimes causes a runtime error, not sure why.
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">pointer to destination array pointer</param>
/// <param name="dest_size">pointer to size of destination array</param>
void mergeDynamic(const char *str1, const char *str2, char **dest, int *dest_size);

/// <summary>
/// My custom merge function using a dynamically-resized array.
/// Causes errors much less, by creating an array one time with enough space.
/// This is the way I'd recommend doing it, one-and-done.
/// </summary>
/// <param name="str1">First string to merge</param>
/// <param name="str2">Second string to merge</param>
/// <param name="dest">pointer to destination array pointer</param>
/// <param name="dest_size">pointer to size of destination array</param>
void mergeDynamicBetter(const char* str1, const char* str2, char** dest, int* dest_size);

#endif