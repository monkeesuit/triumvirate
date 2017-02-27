#include <stdio.h>
#include "buffer.h"

#define SIZE 500

char *buffer[SIZE];

int main() {
  
  read_into_buffer();       // Place message into gloabl buffer; from buffer.h
  
  printf("%s\n", buffer);
  
  return 0;
}
