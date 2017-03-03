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
void display(struct KeySpaceElement *key) {
  int i;
  
  // walk the linked-list
  while(key != NULL) {
    printf("%c\n", key->key);               // display english letter
    printf("[");
    for(i=0; i<key->frequency; i++) {       // display cipher digits
      printf("%d,",key->values[i]);
    }
    printf("]\n\n");
    
    key = key->next;
  }
}

struct KeySpaceElement * parse_data(struct KeySpaceElement *entry) {
  int i, j, k;
  
  int index = 0;
  int line_counter, line_character_counter = 0;
  int line_leftbound, line_rightbound = 0;
  int digit_leftbound, digit_rightbound = 0;
  int digit_character_counter = 0;
  char digit[4];
  char letter;
  
  struct KeySpaceElement *head = entry;
  
  // Parse key data and put it in KeySpaceElement structure
  for (i = 1; i < strlen(data); i++) {
    
    // [-DEBUG-] printf("%c",data[i]);
    
    if (data[i] != '\n') {               // If we encounter a non newline character we just increment the line_character_counter
      line_character_counter += 1;
    
    } else if (data[i] == '\n') {        // If we encounter a newline character we do some stuff
      line_character_counter += 1;
      
      if (line_counter % 2 == 0) {                    // If the line is an even line in our text file then it contains the letter
        line_counter += 1;                                            // increment line_counter
        
        
        // Get line - contains letter
        line_rightbound = line_leftbound + line_character_counter;    // Use bounds to slice buffer in a way that we can pull out the useful information
                                                                      // line_leftbound initializes to 0 and then keeps the index of the last newline character encountered
                                                                      // line_rightbound will equal the next newline character in the file
        // [-DEBUG-]
        printf("Key:\tl:%d\tr:%d\n",line_leftbound, line_rightbound);
        
        
        letter = data[line_leftbound];                            // Get letter from file
        // [-DEBUG-]
        printf("%c\n",letter);

        
        line_leftbound = line_rightbound;                             // Update line_leftbound
        
        
        
      } else if (line_counter % 2 == 1) {             // If the line is an odd line in our text file then it contains the cipher digits
        line_counter += 1;                                            // increment line_counter
        
        // Get line - contains cipher digits
        digit_leftbound = line_leftbound;                             // cipher digits need to be manipulated to be cast from char to int
                                                                      // we must use bounds to slice the line up and extract the digit
                                                                      // digit_leftbound is initialized to 0 and keeps track of the last comma encounterd
        
        line_rightbound = line_leftbound + line_character_counter;
        // [-DEBUG-]
        printf("Value:\tl:%d\tr:%d\n",line_leftbound, line_rightbound);
        
        // [-DEBUG-] printf("\n");
        
        for (j = line_leftbound + 1 ; j < line_rightbound; j++) {     // loop through line
          
          if (data[j] != ',') {                                       // If the character is not a comma then it is a digit, count it
            digit_character_counter += 1;
            
          } else if (data[j] == ',') {                                 // if the character is a comma then we have found the rightbound of the digit
            digit_character_counter += 1;
            
            digit_rightbound = digit_leftbound + digit_character_counter;
            
            memset(digit, 0, sizeof(digit));
            for (k = digit_leftbound; k < digit_rightbound; k++) { // get the cipher digit out of data
              digit[index] = data[k];                                   // put cipher digit in digit array
              index += 1;
            }
            
            // [-DEBUG-]
            printf("%d,",atoi(digit));
            
            index = 0;
            
            digit_leftbound = digit_rightbound;                        // update digit_leftbound
            digit_character_counter = 0;
            
            // Put key's cipher digit in its structure as an int
            //entry = head;
            while(entry != NULL) {
              
              if (entry->key == letter){
                entry->values[ entry->frequency - entry->remaining ] = atoi(digit);
                entry->remaining -= 1;
                break;
              }
              
              entry = entry->next;
            }// Cipher Digit has been entered
          }// Done processing digit
        }// Done looping over digit line
        // [-DEBUG-]
        printf("\n");
        line_leftbound = line_rightbound;
      }// Done processing line of digits
      line_character_counter = 0;
    }// Done processing line
  }// Done processing data
  return head;
}

int main(void) {
  int i;
  
  struct KeySpaceElement *key;
  
  // Build key space
  for (i=0; i<27; i++) {
    head = push(english_letters[i],frequency[i]);
  }
  
  // Get key data
  read_in_data();
  
  // Parse key data
  key = parse_data(head);
  
  display(key);
}