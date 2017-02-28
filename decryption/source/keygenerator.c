#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "prototype.h"
#include "arrays.h"

int cipherdigits[106];

// A KeySpaceElement consists of:
//	a key: 		which is one of the english letters
//	the frequency:	which is the frequency of the occurence of that letter
//	values:		which is an array of digits that the key can encode to

struct KeySpaceElement {
  char key;
  int frequency;
  int remaining;
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
  entry->remaining = frequency;
  entry->next = head;
  head = entry;
}

// Display the linked-list
void display() {
  int i;
  struct KeySpaceElement *entry = head;
  
  while(entry != NULL) {
    printf("(%c,%d)\n[", entry->key, entry->frequency);
    
    for(i=0; i<entry->frequency; i++) {
      printf("%d,",entry->values[i]);
    }
    printf("]\n");
    
    entry = entry->next;
  }
}

void pick() {
  srand(time(NULL));
  int i, j, index, letter, digit, nop, keyed;
  
  keyed=0;
  nop=0;
  
  while(keyed<27) {
    index = rand() % 27;
    letter = english_letters[index];
    
    printf("Keying: %c\n",letter);
    
    struct KeySpaceElement *entry = head;
    
    while(entry != NULL) {
      if (entry->key==letter) {
        printf("Found! (%c,%c)\n",entry->key,letter);
        if(entry->remaining >0){
          index = rand() % (106-nop);
          
          for(j = 0; j<(106); j++) {
            printf("%d,",cipherdigits[j]);
          }
          printf("\n");
          
          digit = cipherdigits[index];
          printf("Inserting: %d\n",digit);
          
          entry->values[entry->frequency-entry->remaining] = digit;
          entry->remaining -= 1;
          printf("Remaining: %d\n",entry->remaining);
          if (entry->remaining == 0) {
            keyed += 1;
            printf("Keyed: %d\n",keyed);
          }
          
          cipherdigits[index] = cipherdigits[105-nop];
          cipherdigits[105-nop] = '\0';
          nop++;
          break;
        }
      }
      entry = entry->next;
    }
    
  }
}

int main(){
  int i;
  
  for (i=0;i<106;i++) {
    cipherdigits[i]=i;
  }
  
  for (i=0; i<27; i++) {
    push(english_letters[i],frequency[i]);    // Initialize Key Space; from keygenerator.h
  }
  
  display();
  pick();
  display();
  
  return 0;	
}
