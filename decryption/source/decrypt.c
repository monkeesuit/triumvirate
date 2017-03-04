#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arrays.h"
#include "loadkey.h"
#include "hadriansfunctions.h"

#define SIZE 500


// decrypts a cipher digit to an english letter given a key
char decrypt_digit(struct KeySpaceElement *key, int digit) {
  int i;

  while(key != NULL) {
    for(i=0; i< key->frequency; i++){
      if (key->values[i] == digit) {
        return key->key;
      }
    }
    key = key->next;
  }
}



//*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/*\*/\\



int main() {
  int i;
  char *filename;
  char *data, *rawcipher;
  char message[SIZE];
  int *cipher;
  
  struct KeySpaceElement *head = NULL;
  struct KeySpaceElement *key;
  
  
  printf("\nWelcome to the Decrypt Script!\n");
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
  filename = input(" ciphertext file> ");
  rawcipher = read(filename);
  
  // Process cipher data
  cipher = intcsv(rawcipher);
  
  // Loop through ciphertext - decrypting each digit
  for (i=0; i<SIZE; i++) {;
    message[i] = decrypt_digit(key, cipher[i]);
  }
  
  // Print decrypted message
  printf("\nPlaintext:\n%s\n\n", message);
  
  return 0;
}
