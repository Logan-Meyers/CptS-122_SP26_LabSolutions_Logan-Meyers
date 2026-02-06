/*
- Programmer: Logan Meyers
- Class: CptS 122 Lab #11
- Assignment: Lab 3 Tasks 1 & 2
- Date: 02/05/2026
- Decription: Doubly Linked List!

- File: linkedlist.c
- Description: definitions for linked list function from linkedlist.h
*/

#include "linkedlist.h"

/* ------------------------------ Demo Functions ------------------------------ */

void demoManual() {
	printf("\n----- Demoing Linked List with manual entries\n");
	Contact a = { .email = "1234@hotmail.com", .name = "Jeremy", .phone = "5095551465", .title = "bossman" };
	Contact b = { .email = "wahoo@yahoo.com", .name = "Clarkson", .phone = "5091115673", .title = "potato maker" };
	Contact c = { .email = "Alex123@gmail.com", .name = "Alexx", .phone = "9072642613", .title = "banana man" };
	Contact d = { .email = "woxwox5@wsu.edu", .name = "Wozniak", .phone = "5556667746", .title = "copmuter dudes" };
	Contact e = { .email = "YIP@yip.com", .name = "Clarkson", .phone = "5091115674", .title = "potato maker pro" };
	Node* list = NULL;
	insertContactInOrder(&list, b);
	insertContactInOrder(&list, a);
	insertContactInOrder(&list, c);
	insertContactInOrder(&list, d);

	printf("This is the current list:\n");
	printList(list);

	deleteContact(&list, c);
	deleteContact(&list, d);

	printf("After deleting %s and %s:\n", c.name, d.name);
	printList(list);
}

void demoRW() {
	printf("\n----- Demoing Linked List with reading/writing to/from a file\n");

	Node* list = NULL;

	FILE* infile = fopen(INFILE, "r");
	loadContacts(infile, &list);
	fclose(infile);

	printf("\nAfter reading the file, here is our list:\n");
	printList(list);

	deleteContact(&list, (Contact) { .name = "David Lee" });
	deleteContact(&list, (Contact) { .name = "Benjamin Scott" });
	deleteContact(&list, (Contact) { .name = "Grace Roberts" });

	FILE* outfile = fopen(OUTFILE, "w");
	storeContacts(outfile, list);
	fclose(outfile);

	destroy(&list);

	infile = fopen(OUTFILE, "r");
	loadContacts(infile, &list);
	fclose(infile);

	printf("\nAfter deleting a couple contacts, writing the file, then loading it again : \n");
	printList(list);

	destroy(&list);
}

/* ------------------------------ Linked List Functions ------------------------------ */

Node* createNode(Contact newData) {
	Node* pMem = malloc(sizeof(Node)); // allocating 54 or 58 bytes

	if (pMem != NULL)
	{
		// we allocated a Node successfully on the heap

		// we can now initialize it
		pMem->data = newData; // struct assignment
		pMem->pNext = NULL;
		pMem->pPrev = NULL;  // NEW FOR DOUBLY
	}

	return pMem;
}

// Description: Uses makeNode () to allocate space for a new Node and inserts the new Node at the front 
// Returns: TRUE if memory was  allocated for a Node; FALSE otherwise 
Boolean insertFront(Node** pList, Contact newData) {
	Node* newNode = createNode(newData);

	if (newNode == NULL) return FALSE;

	newNode->pNext = *pList;
	if (*pList) (*pList)->pPrev = newNode;  // set backwards link, if list isn't empty -- NEW FOR DOUBLY
	// alternative: newNode->pNext->pPrev = newNode;

	*pList = newNode;

	return TRUE;
}

Boolean insertContactInOrder(Node** pList, Contact newData) {
	// try to create space for a new node, return if failed
	Node* pMem = createNode(newData);
	if (pMem == NULL) return FALSE;

	// pcur and pnext
	Node *pCur = *pList, *pPrev = NULL;

	// find the spot in the loop to insert
	while (pCur != NULL && strcmp(pCur->data.name, newData.name) < 0) {
		pPrev = pCur;
		pCur = pCur->pNext;
	}

	// insert node conditionally

	// pList null, 

	// start of list, basically insertAtFront
	if (pPrev == NULL) {
		// attach new node to rest of list
		pMem->pNext = *pList;

		// attach rest of list to new node if rest of list exists
		if (*pList) (*pList)->pPrev = pMem;  // NEW FOR DOUBLY

		*pList = pMem;

	}
	// somewhere in the middle or the end
	else {
		// attach new node to rest of list
		pMem->pNext = pCur;  // pmem forward
		pMem->pPrev = pPrev;  // pmem backwards -- NEW FOR DOUBLY

		pPrev->pNext = pMem;  // prev to pmem forwards
		if (pCur) pCur->pPrev = pMem;  // current to pmem backwards -- NEW FOR DOUBLY
	}

	return TRUE;
}

Boolean deleteContact(Node** pList, Contact searchContact) {
	// variables
	Node *pCur = *pList, *pPrev = NULL;

	// find node to remove
	while (pCur != NULL && strcmp(pCur->data.name, searchContact.name) != 0) {
		pPrev = pCur;
		pCur = pCur->pNext;
	}

	// no node found, default success
	if (pCur == NULL) return FALSE;

	// no prev, set start of list
	if (pPrev == NULL) {
		*pList = pCur->pNext;  // set new beginning to list
		if (*pList) (*pList)->pPrev = NULL;  // remove link to node we are freeing if a next exists -- NEW FOR DOUBLY
	}

	// prev exists, middle of list
	else {
		pPrev->pNext = pCur->pNext;  // set forward link to skip node we want to remove
		if (pCur->pNext) pCur->pNext->pPrev = pPrev;  // set backwards link from next to prev, if next exists -- NEW FOR DOUBLY
	}

	// free node
	free(pCur);

	return TRUE;
}

// FOR DOUBLY: no changes needed
Boolean editContact(Node* pList, Contact searchContact) {
	// variable
	Node *pCur = pList;

	// find node to edit
	while (pCur != NULL && strcmp(pCur->data.name, searchContact.name) != 0) {
		pCur = pCur->pNext;
	}

	// no node, exit successfully
	if (pCur == NULL) return TRUE;

	// edit node by reassigning data
	pCur->data = searchContact;

	return TRUE;
}

// FOR DOUBLY: no changes needed
Boolean loadContacts(FILE* infile, Node** pList) {
	if (!infile)
		return FALSE;

	char line[150] = "";
	while (fgets(line, 150, infile)) {
		Contact newContact;

		// this assumes fully well-formed input data
		strcpy(newContact.name, strtok(line, ","));
		strcpy(newContact.phone, strtok(NULL, ","));
		strcpy(newContact.email, strtok(NULL, ","));
		strcpy(newContact.title, strtok(NULL, ","));

		insertContactInOrder(pList, newContact);
	}

	return TRUE;
}

// FOR DOUBLY: no changes needed
Boolean storeContacts(FILE* outfile, Node* pList) {
	if (outfile == NULL) return FALSE;

	Node* pCur = pList;

	while (pCur != NULL) {
		fprintf(outfile, "%s,%s,%s,%s", pCur->data.name, pCur->data.phone, pCur->data.email, pCur->data.title);
		
		pCur = pCur->pNext;
	}
	
	return TRUE;
}
// FOR DOUBLY: no changes needed
void destroy(Node** list) {
	while (*list != NULL) {
		Node* next = (*list)->pNext;
		free(*list);
		*list = next;
	}
}

// FOR DOUBLY: no changes needed
void printList(Node* pHeadCopy)
{
	Node* pCur = pHeadCopy; // let's start at the beginning of the list

	printf("--> "); // displays even if the list is empty

	while (pCur != NULL) // while we haven't reached the end of the list
	{
		// display the current Movie record
		printf("%s --> ", pCur->data.name);
		pCur = pCur->pNext; // go to the next node in sequence
	}

	putchar('\n');
}
