#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arrays.h"
#include "loadkey.h"
#include "getfilebyname.h"

#define SIZE 500


// decrypts a cipher digit to an english letter given a key
char decrypt_digit(struct KeySpaceElement *key, int digit) {
  int i;
  printf("DIGIT!!! ->\t(%d)\n",digit);

  while(key != NULL) {
    for(i=0; i< key->frequency; i++){
      printf("CIPHER DIGIT!!! ->\t(%d)\n",key->values[i]);
      if (key->values[i] == digit) {
        printf("\n");
        printf("%c\n",key->key);
        return key->key;
      }
    }
    key = key->next;
  }
}

int main() {
  int i,j;
  char filename[100];
  char digit[4];
  char *data;
  char *rawcipher;
  int cipher[SIZE];
  char message[SIZE];
  
  struct KeySpaceElement *head = NULL;
  struct KeySpaceElement *key;
  
  int leftbound;
  int rightbound;
  int character_counter;
  int index;
  int character;
  
  leftbound = -1;
  rightbound = 0;
  character_counter = 0;
  index = 0;
  character = 0;
  
  
  // Build key space
  for (i=0; i<27; i++) {
    head = push(head,english_letters[i],frequency[i]);
  }
  
  printf("\nProvide the key...\n");
  data = enterfile();
  
  
  // Parse key data
  key = parse_data(head, data);
  
  
  printf("\nProvide the ciphertext to be decrypted...\n");
  rawcipher = enterfile();
  
  
  // Parse ciphertext and produce an cipher int array
  for (i=0; i<strlen(rawcipher); i++){
    if (rawcipher[i] != ','){
      character_counter += 1;
    } else if (rawcipher[i] == ',') {
      character_counter += 1;
      rightbound = leftbound + character_counter;
      for (j=leftbound+1; j<rightbound; j++) {
        digit[index]=rawcipher[j];
        index += 1;
      }
      leftbound = rightbound;
      character_counter = 0;

      index = 0;
      cipher[character] = atoi(digit);
      character += 1;
    }
  }
  
  
  // loop through ciphertext - decrypting each digit
  for (i=0; i<SIZE; i++) {;
    message[i] = decrypt_digit(key, cipher[i]);
  }
  
  printf("%s\n", message);
  
  return 0;
}
