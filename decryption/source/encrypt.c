#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 500

#include "arrays.h"
#include "buffer.h"
#include "keygenerator.h"

char *buffer[SIZE];

int main() {
  int i;
  
  read_into_buffer();       // Place message into gloabl buffer; from buffer.h
  
  printf("%s\n", buffer);
  
  for (i=0; i<27; i++) {
    push(english_letters[i],frequency[i]);
  }
  display();
  
  return 0;
}
