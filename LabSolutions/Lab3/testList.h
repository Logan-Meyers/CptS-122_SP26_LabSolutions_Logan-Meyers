/*
- Programmer: Logan Meyers
- Class: CptS 122 Lab #11
- Assignment: Lab 3 Tasks 1 & 2
- Date: 02/05/2026
- Decription: Doubly Linked List!

- File: testList.h
- Description: function declerations and structs for testing the doubly linked list
*/


#pragma once

#ifndef test_h
#define test_h

#include "linkedlist.h"

/* ------------------------------ Test Runners ------------------------------ */

void printTestResult(char* name, int result);
void testAll();

/* ------------------------------ Unit Tests ------------------------------ */

int testCreateNode();
int testInsertFront();
int testInsertContactInOrder();
int testDeleteContact();
int testEditContact();
int testLoadContacts();
int testStoreContacts();

#endif