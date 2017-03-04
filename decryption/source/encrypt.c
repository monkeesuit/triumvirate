#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arrays.h"
#include "loadkey.h"
#include "hadriansfunctions.h"

#define SIZE 500


// encrypts a character to a digit
int encrypt_character(struct KeySpaceElement *key, char character, int position) {
  int choice, encryptedbit;
  
  while(key != NULL) {
    if (key->key == character) {
      choice = position % key->frequency;
      return key->values[choice];
    }
    key = key->next;
  }
}



//*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/\\



int main() {
  int i;
  char *filename;
  char *data;
  char *message;
  int cipher[SIZE];
  
  struct KeySpaceElement *head = NULL;
  struct KeySpaceElement *key;


  
  printf("\nWelcome to the Encrypt Script!\n");
  // Input the key
  filename = input(" key file> ");
  data = read(filename);
  
  // Build key space
  for (i=0; i<27; i++) {
    head = initializekey(head,english_letters[i],frequency[i]);
  }
  
  // Parse key data
  key = loadkey(head, data);

  // Input the message
  filename = input(" message file> ");
  message = read(filename);

  // Loop throgh the message - encrypting each character
  for (i=0; i<500; i++) {
    cipher[i] = encrypt_character(key, message[i], i);
  }
  
  // Display ciphertext
  printf("\nCiphertext:\n");
  for(i=0;i<500;i++) {
    printf("%d,",cipher[i]);
  }
  printf("\n");
  
  return 0;
}
