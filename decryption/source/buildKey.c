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
  
  int index =0;
  int line_count = 0;
  int counter = 0;
  int left_bound = 0;
  int right_bound = 0;
  int value_index = -1;
  int rb = 0;
  int lb = 0;
  int c = 0;
  char digit[4];
  char assign_key;
  
  int i, j, k;
  
  struct KeySpaceElement *entry;
  struct KeySpaceElement *head_a;
  
  
  for (i=0; i<27; i++) {
    head_a = push(english_letters[i],frequency[i]);
  }
  
  read_in_data();
  
  for (i = 1; i < strlen(data); i++) {
    if (data[i] != '\n') {
      counter += 1;
    }
    if (data[i] == '\n') {
      if (line_count % 2 == 0) {
        counter += 1;
        right_bound = left_bound + counter;
        assign_key = data[left_bound + 1];
        

        
        left_bound = right_bound;
        counter = 0;
        line_count += 1;
        
      } else {
        counter += 1;
        lb = left_bound;
        right_bound = left_bound + counter;
        
        for (j = left_bound + 1 ; j < right_bound; j++) {
          
          if (data[j] != ',') {
            c += 1;
            
          } else if (data[j] == ',') {
            c += 1;
            
            rb = lb + c;
            
            memset(digit, 0, sizeof(digit));
            for (k = lb + 1; k < rb; k++) {
              digit[index] = data[k];
              index += 1;
            }
            index = 0;
            
            lb = rb;
            c = 0;
            value_index += 1;
            
            entry = head_a;
            while(entry != NULL) {

              if (entry->key == assign_key){
                entry->values[ entry->frequency - entry->remaining ] = atoi(digit);
                entry->remaining -= 1;
                break;
              }
              
              entry = entry->next;
            }
            
          }
        }
        
        left_bound = right_bound;
        counter = 0;
        line_count +=1;
      }
    }
  }
  display();
}
