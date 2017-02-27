// A KeySpaceElement consists of:
//	a key: 		which is one of the english letters
//	the frequency:	which is the frequency of the occurence of that letter
//	values:		which is an array of digits that the key can encode to

// .c file


#include <stdlib.h>
#include <stdio.h>

void push(char, int);        // Prototype needs to be defined here or compiler throws implicit call error

struct KeySpaceElement {	
	char key;
	int frequency;
	char values[60];
	struct KeySpaceElement *next;
};  

// Initialize the linked-list
struct KeySpaceElement *head = NULL;

// Put an entry in the linked-list
void push(char key, int frequency) {
	struct KeySpaceElement *entry;
	entry = malloc(sizeof(struct KeySpaceElement));
	
	entry->key = key;
	entry->frequency = frequency;
	entry->next = head;
	head = entry;
}

// Display the linked-list
void display() {
	struct KeySpaceElement *entry = head;
	
	while(entry != NULL) {
		printf("(%c,%d)", entry->key, entry->frequency);
		entry = entry->next;
	}
}
