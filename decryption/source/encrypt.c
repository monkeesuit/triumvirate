#include <stdio.h>
//#include <string.h>     not needed
//#include <stdlib.h>     not needed

//#define SIZE 500        

#include "arrays.h"               //Had to define the function prototypes here
void push(char k, int f);
void display();


//char *buffer[SIZE];       Not putting anything into the buffer - Also should just be char *buffer or char buffer[SIZE] (no pointer)

int main() {
  int i;
  
//  read_into_buffer();                     //  Gives error since it's not currently reading anything     // Place message into gloabl buffer; from buffer.h
                                              
//  printf("%s\n", buffer);                 // Nothing to print
  
  for (i=0; i<27; i++) {
    push(english_letters[i],frequency[i]);    // Initialize Key Space; from keygenerator.h
  }
  display();                    
  
  return 0;
}
