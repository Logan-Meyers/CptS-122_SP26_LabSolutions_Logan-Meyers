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