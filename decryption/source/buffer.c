// This function places a message in a global buffer

#include <unistd.h>

#define SIZE 500;

int read_into_buffer() {
  extern char buffer[SIZE];
  
  read(0, buffer, SIZE);
  
  return 0;
}

