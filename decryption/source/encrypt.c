#include <stdio.h>
#include "prototype.h"
#include "arrays.h"               //Had to define the function prototypes here

int main() {
  int i;
  
//  read_into_buffer();                       // Place message into gloabl buffer; from buffer.h
                                              
//  printf("%s\n", buffer);                   
  
  for (i=0; i<27; i++) {
    push(english_letters[i],frequency[i]);    // Initialize Key Space; from keygenerator.h
  }
  display();                    
  
  return 0;
}
