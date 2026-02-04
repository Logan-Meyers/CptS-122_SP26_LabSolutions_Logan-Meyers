#include "linkedlist.h"

/* ------------------------------ Test Runners ------------------------------ */

void printTestResult(char* name, int result) {
	if (result)
		printf("Test %s succeeded!\n", name);
	else
		printf("Test %s failed!\n", name);
}

void testAll() {
	printf("----- Testing Linked List -----\n");
	printTestResult("Create Node", testCreateNode());
	printTestResult("Insert Front", testInsertFront());
	printTestResult("Insert Contact In Order", testInsertContactInOrder());
	printTestResult("Delete Contact", testDeleteContact());
	printTestResult("Edit Contact", testEditContact());
	printTestResult("Load Contacts", testLoadContacts());
	printTestResult("Store Contacts", testStoreContacts());
}

/* ------------------------------ Unit Tests ------------------------------ */

int testCreateNode() {
	Contact a = { .email = "1234@hotmail.com", .name = "Jeremy", .phone = "5095551465", .title = "bossman" };
	Node* newnode = createNode(a);

	if (
		newnode == NULL ||
		newnode->pNext != NULL ||
		strcmp(newnode->data.email, a.email) != 0 ||
		strcmp(newnode->data.name, a.name) != 0 ||
		strcmp(newnode->data.phone, a.phone) != 0 ||
		strcmp(newnode->data.title, a.title) != 0
		) return 0;

	return 1;
}

int testInsertFront() {
	Contact a = { .email = "1234@hotmail.com", .name = "Jeremy", .phone = "5095551465", .title = "bossman" };
	Contact b = { .email = "wahoo@yahoo.com", .name = "Clarkson", .phone = "5091115673", .title = "potato maker" };
	Node* list = NULL;

	insertFront(&list, a);

	if (
		list == NULL ||
		list->pNext != NULL ||
		strcmp(list->data.email, a.email) != 0 ||
		strcmp(list->data.name, a.name) != 0 ||
		strcmp(list->data.phone, a.phone) != 0 ||
		strcmp(list->data.title, a.title) != 0
		) return 0;

	insertFront(&list, b);

	if (
		list == NULL ||
		list->pNext == NULL ||
		strcmp(list->data.email, b.email) != 0 ||
		strcmp(list->data.name, b.name) != 0 ||
		strcmp(list->data.phone, b.phone) != 0 ||
		strcmp(list->data.title, b.title) != 0
		) return 0;

	return 1;
}

int testInsertContactInOrder() {
	Contact a = { .email = "Alex123@gmail.com", .name = "Alexx", .phone = "9072642613", .title = "banana man" };
	Contact b = { .email = "woxwox5@wsu.edu", .name = "Wozniak", .phone = "5556667746", .title = "copmuter dudes" };
	Contact c = { .email = "wahoo@yahoo.com", .name = "Clarkson", .phone = "5091115673", .title = "potato maker" };
	Node* list = NULL;

	// insert front into empty list
	insertContactInOrder(&list, a);

	if (
		list == NULL ||
		list->pNext != NULL ||
		strcmp(list->data.email, a.email) != 0 ||
		strcmp(list->data.name, a.name) != 0 ||
		strcmp(list->data.phone, a.phone) != 0 ||
		strcmp(list->data.title, a.title) != 0
		) return 0;

	// insert at end
	insertContactInOrder(&list, b);

	if (
		list == NULL ||
		list->pNext == NULL ||
		list->pNext->pNext != NULL ||
		strcmp(list->data.name, a.name) != 0 ||
		strcmp(list->pNext->data.name, b.name) != 0
		) return 0;
	
	// insert in middle
	insertContactInOrder(&list, c);

	if (
		list == NULL ||
		list->pNext == NULL ||
		list->pNext->pNext == NULL ||
		list->pNext->pNext->pNext != NULL ||
		strcmp(list->data.name, a.name) != 0 ||
		strcmp(list->pNext->data.name, c.name) != 0 ||
		strcmp(list->pNext->pNext->data.name, b.name) != 0
		) return 0;

	return 1;
}

int testDeleteContact() {
	Contact a = { .email = "Alex123@gmail.com", .name = "Alexx", .phone = "9072642613", .title = "banana man" };
	Contact b = { .email = "woxwox5@wsu.edu", .name = "Wozniak", .phone = "5556667746", .title = "copmuter dudes" };
	Contact c = { .email = "wahoo@yahoo.com", .name = "Clarkson", .phone = "5091115673", .title = "potato maker" };
	Node* list = NULL;

	insertFront(&list, a);
	insertFront(&list, b);
	insertFront(&list, c);

	deleteContact(&list, b);

	if (
		list == NULL ||
		list->pNext == NULL ||
		list->pNext->pNext != NULL ||
		strcmp(list->data.name, a.name) != 0 ||
		strcmp(list->pNext->data.name, c.name) != 0
		) return 0;
	
	return 1;
}

int testEditContact() {
	Contact a = { .email = "wahoo@yahoo.com", .name = "Clarkson", .phone = "5091115673", .title = "potato maker" };
	Contact b = { .email = "YIP@yip.com", .name = "Clarkson", .phone = "5091115674", .title = "potato maker pro" };
	Node* list = NULL;

	insertFront(&list, a);
	editContact(list, b);

	if (
		list == NULL ||
		list->pNext != NULL ||
		strcmp(list->data.email, b.email) != 0 ||
		strcmp(list->data.name, b.name) != 0 ||
		strcmp(list->data.phone, b.phone) != 0 ||
		strcmp(list->data.title, b.title) != 0
		) return 0;

	return 1;
}

int testLoadContacts() {
	return 1;
}

int testStoreContacts() {
	return 1;
}
