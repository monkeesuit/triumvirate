#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arrays.h"
#include "loadkey.h"
#include "getfilebyname.h"

#define SIZE 500



char message[SIZE];
int cipher[SIZE];
int cipherdigits[106];


void encrypt_character(struct KeySpaceElement *key, char character, int position) {
  int choice, encryptedbit;
  
  while(key != NULL) {
    if (key->key == character) {
      choice = position % key->frequency;
      encryptedbit = key->values[choice];
      cipher[position] = encryptedbit;
      break;
    }
    key = key->next;
  }
}

int main() {
  int i;
  char filename[100];
  char *data;
  char *message;
  
  struct KeySpaceElement *head = NULL;
  struct KeySpaceElement *key;
  
  
  //  [-DEBUG-]printf("start...\n");


  // Build key space
  for (i=0; i<27; i++) {
    //  [-DEBUG-]printf("Push Iteration: %d...\n", i);
    
    head = push(head,english_letters[i],frequency[i]);
  }
  //  [-DEBUG-]printf("Key Initialized\n", i);display(head);

  data = enterfile();
  // [-DEBUG-]printf("File Read!\n%s\n",data);

  
  // Parse key data
  key = parse_data(head, data);
  // [-DEBUG-]
  printf("Key Made!\n");
  display(key);
  
  
  
  message = enterfile();
  // [-DEBUG-]printf("File Read!\n%s\n",data);

  
  
  // Encrypt the message
  for (i=0; i<500; i++) {
    encrypt_character(key, message[i], i);
  }
  
  //  [-DEBUG-]
  
  printf("%s\n", message);
  for(i=0;i<500;i++) {
    printf("%d,",cipher[i]);
  }
  
  
  return 0;
}
