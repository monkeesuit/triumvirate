#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void printList();

char  english_letters[27] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                                't', 'u', 'v', 'w', 'x', 'y', 'z'
			    };

int frequency[27] = { 19, 7, 1, 2, 4, 10,  2, 2, 5, 6, 1, 1, 3, 2, 6, 6, 2, 1, 5, 5, 7, 2, 1, 2, 1, 2, 1 };


typedef struct KeySpaceElement {
	char key;
	int frequency;
	char cipher_characters[60];
   	struct KeySpaceElement * next;
} keyspaceelement;

keyspaceelement *head = NULL;
//malloc(sizeof(keyspaceelement));
//if (head == NULL) {
//    return 1;
//}``

void push( struct KeySpaceElement ** head, char key, int frequency) {
	keyspaceelement * entry = malloc(sizeof(keyspaceelement));
    entry->key = key;
	entry->frequency = frequency;
    entry->next = *head;
    *head = entry;
    printList();
}

void printList() {
    keyspaceelement *ptr = head;
    printf("(%c, %d) ", ptr->key, ptr->frequency);
}

int main(void) {
//     keyspaceelement *head = malloc(sizeof(keyspaceelement));
//     if (head == NULL) {
//     return 1;
//  
    for (int i = 0; i < 27; i++) {
	   push(&head, english_letters[i], frequency[i]);
    };
}
