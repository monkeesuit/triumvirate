#include <stdlib.h>
#include <stdio.h>
#include "protoype.h"

// A KeySpaceElement consists of:
//	a key: 		which is one of the english letters
//	the frequency:	which is the frequency of the occurence of that letter
//	values:		which is an array of digits that the key can encode to

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

void pick() {
  srand(time(NULL));
  int i, j, index, letter, digit, nop;
  
  nop=0;
  
  for(i=0;i<10;i++) {
    index = rand() % 26;
    letter = english_letters[index];
    
    struct KeySpaceElement *entry = head;
    
    while(entry != NULL) {
      if (entry->key==letter) {
        if(entry->frequency !=0){
          index = rand() % (105-nop);
          
          for(j = 0; j<(106); j++) {
            printf("%d,",cipherdigits[j]);
          }
          printf("\n");
          digit = cipherdigits[index];
          printf("[%d]\n", digit);
          cipherdigits[index] = cipherdigits[105-nop];
          cipherdigits[105-nop] = '\0';
          nop++;
        }
      }
      entry = entry->next;
    }
  }
}
