#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "arrays.h"

#define SIZE 500

char data[SIZE];

int read_in_data() {
  extern char data[SIZE];
  read(0, data, SIZE);
  return 0;
}

// Initialize the linked-lis
struct KeySpaceElement *head = NULL;

struct KeySpaceElement {
  char key;
  int frequency;
  int remaining;
  char values[60];
  struct KeySpaceElement *next;
};
// Put an entry in the linked-list
struct KeySpaceElement * push(char key, int frequency) {
  struct KeySpaceElement *entry;
  entry = malloc(sizeof(struct KeySpaceElement));
  
  entry->key = key;
  entry->frequency = frequency;
  entry->remaining = frequency;
  entry->next = head;
  head = entry;
  
  return head;
}

// Display the linked-list
void display() {
  int i;
  
  // walk the linked-list
  struct KeySpaceElement *entry = head;
  while(entry != NULL) {
    printf("%c\n", entry->key);               // display english letter
    printf("[");
    for(i=0; i<entry->frequency; i++) {       // display cipher digits
      printf("%d,",entry->values[i]);
    }
    printf("]\n\n");
    
    entry = entry->next;
  }
}

int main(void) {
  int i, j, k;
  
  int index = 0;
  int line_counter, line_character_counter = 0;
  int line_leftbound, line_rightbound = 0;
  int digit_leftbound, digit_rightbound = 0;
  int digit_character_counter = 0;
  char digit[4];
  char letter;
  
  struct KeySpaceElement *entry;
  
  
  // Build key space
  for (i=0; i<27; i++) {
    head = push(english_letters[i],frequency[i]);
  }
  
  
  // Get key data
  read_in_data();
  
  
  // Parse key data and put in out KeySpaceElement structure
  for (i = 1; i < strlen(data); i++) {
    if (data[i] != '\n') {               // If we encounter a non newline character we just increment the line_character_counter
      line_character_counter += 1;
      
    } else if (data[i] == '\n') {        // If we encounter a newline character we do some stuff
      line_character_counter += 1;

      if (line_counter % 2 == 0) {            // If the line is an even line in our text file then it contains the letter
        line_counter += 1;                                            // increment line_counter

        
        // Get line - contains letter
        line_rightbound = line_leftbound + line_character_counter;    // Use bounds to slice buffer in a way that we can pull out the useful information
                                                                      // line_leftbound initializes to 0 and then keeps the index of the last newline character encountered
                                                                      // line_rightbound will equal the next newline character in the file
        
        letter = data[line_leftbound + 1];                            // Get letter from file
        
        line_leftbound = line_rightbound;                             // Update line_leftbound
        
        
        
      } else if (line_counter % 2 == 1) {     // If the line is an odd line in our text file then it contains the cipher digits
        line_counter += 1;                                            // increment line_counter
        
        // Get line - contains cipher digits
        digit_leftbound = line_leftbound;                             // cipher digits need to be manipulated to be cast from char to int
                                                                      // we must use bounds to slice the line up and extract the digit
                                                                      // digit_leftbound is initialized to 0 and keeps track of the last comma encounterd
        
        line_rightbound = line_leftbound + line_character_counter;
        for (j = line_leftbound + 1 ; j < line_rightbound; j++) {
          
          if (data[j] != ',') {                                       // If the character is not a comma then it is a digit, count it
            digit_character_counter += 1;
            
          } else if (data[j] == ',') {                                 // if the character is a comma then we have found the rightbound of the digit
            digit_character_counter += 1;
            
            digit_rightbound = digit_leftbound + digit_character_counter;
            
            memset(digit, 0, sizeof(digit));
            for (k = digit_leftbound + 1; k < digit_rightbound; k++) { // get the cipher digit out of data
              digit[index] = data[k];                                   // put cipher digit in digit array
              index += 1;
            }
            index = 0;
            
            digit_leftbound = digit_rightbound;                        // update digit_leftbound
            digit_character_counter = 0;
            
            // Put key's cipher digit in its structure as an int
            entry = head;
            while(entry != NULL) {
              
              if (entry->key == letter){
                entry->values[ entry->frequency - entry->remaining ] = atoi(digit);
                entry->remaining -= 1;
                break;
              }
              
              entry = entry->next;
            }
            // Key has been entered
            
          }
        }
        
        line_leftbound = line_rightbound;
      }
      line_character_counter = 0;
    }// Done processing line
  }// Done processing data
  
  display();
}
