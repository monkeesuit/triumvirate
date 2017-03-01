#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
struct KeySpaceElement * push(char key, int frequency) {
  struct KeySpaceElement *entry;
  entry = malloc(sizeof(struct KeySpaceElement));
  
  entry->key = key;
  entry->frequency = frequency;
  entry->remaining = frequency;
  entry->next = head;
  head = entry;
  
  return head;
}

// Key the linked-list
void pick() {
  int i, j, index, letter, digit, nop, keyed;
  
  keyed=0;                                               // keyed -> keeps tracks of elements that have been fully keyed
  nop=0;                                                 // nop   -> keeps track of how many cipher digits have been chosen
  
  // loop until all have been keyed
  while(keyed<27) {
    index = rand() % 27;                                    // pick a random letter (<space>,a,b,c,...z)
    letter = english_letters[index];
    
    // walk the linked-list
    struct KeySpaceElement *entry = head;
    while(entry != NULL) {
      if (entry->key==letter) {                               // if we find the entry that matches the random letter we chose,
        if(entry->remaining >0){                              // and it is not keyed (remaining=0 => keyed +1)
          entry->remaining -= 1;
          if (entry->remaining == 0) {
            keyed += 1;
          }
          
          index = rand() % (106-nop);                         // pick a number from cipher digits
          digit = cipherdigits[index];
          entry->values[entry->frequency - (entry->remaining+1)] = digit;   // and put it in the entries values array
          
          // pop the chosen digit from cipherdigits
          cipherdigits[index] = cipherdigits[105-nop];    // this overwrites the chosen digit with the last non-nop digit in cipher digits
          cipherdigits[105-nop] = '\0';                   // and then nop the copied digit at the end of the list
          nop++;                                          // increment the nop variable to indicate that cipher digits is one unit smaller
          break;
        }
      }
      entry = entry->next;
    }
    
  }
}



// Writes key to file key.txt
void write_to_file() {
  int i;
  
  FILE *f =fopen("key.txt","w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
  
  // walk the linked-list
  struct KeySpaceElement *entry = head;
  while(entry != NULL) {
    fprintf(f,"%c\n",entry->key);
    for(i=0; i< entry->frequency; i++) {
      fprintf(f,"%d,", entry->values[i]);
    }
    fprintf(f,"\n");
    entry = entry->next;
  }
}



// Display the linked-list
void display() {
  int i;
  
  // walk the linked-list
  struct KeySpaceElement *entry = head;
  while(entry != NULL) {
    printf("%c\n", entry->key);               // display english letter
    printf("[");
    for(i=0; i<entry->frequency; i++) {       // display cipher digits
      printf("%d,",entry->values[i]);
    }
    printf("]\n\n");
    
    entry = entry->next;
  }
}





int main(){
  int i;
  srand(time(NULL));
  
  for (i=0; i<106; i++) {
    cipherdigits[i]=i;
  }
  
  for (i=0; i<27; i++) {
    push(english_letters[i],frequency[i]);
  }
  pick();
  display();
  write_to_file();
  
  return 0;
}
