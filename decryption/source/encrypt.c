#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arrays.h"
#include "prototype.h"

#define SIZE 500

struct KeySpaceElement {
  char key;
  int frequency;
  int remaining;
  char values[60];
  struct KeySpaceElement *next;
};

char buffer[SIZE];
int cipher[SIZE];
int cipherdigits[106];


int read_into_buffer() {
  extern char buffer[SIZE];
  
  read(0, buffer, SIZE);
  
  return 0;
}

void encrypt(char character, int position, struct KeySpaceElement * pointer) {
  int choice, encryptedbit;
  
  struct KeySpaceElement *entry = pointer;
  
  while(entry != NULL) {
    if (entry->key == character) {
      choice = position % entry->frequency;
      encryptedbit = entry->values[choice];
      cipher[position] = encryptedbit;
      break;
    }
    entry = entry->next;
  }
}

int main() {
  int i;
  struct KeySpaceElement * head;
  char character;
  
  read_into_buffer();       // Place message into gloabl buffer; from buffer.h
  
  for (i=0;i<106;i++) {
    cipherdigits[i]=i;
  }
  
  for (i=0; i<27; i++) {
    head = push(english_letters[i],frequency[i]);    // Initialize Key Space; from keygenerator.h
  }
  
  pick();
  display();
  
  for (i=0; i<500; i++) {
    character = buffer[i];
    //printf("%c\n",character);
    encrypt(character, i, head);
  }
  printf("%s\n", buffer);
  
  for(i=0;i<500;i++) {
    printf("%d,",cipher[i]);
  }
  
  return 0;
}
