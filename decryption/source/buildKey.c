#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arrays.h"
#include <unistd.h>
#define SIZE 500

int read_into_buffer();
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

char buffer[SIZE];
int read_into_buffer() {
  extern char buffer[SIZE];
  read(0, buffer, SIZE);
  return 0;
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

    int line_count = 0;
    int counter = 0;
    int left_bound = 0;
    int right_bound = 0;
    int value_index = -1;
    int rb = 0;
    int lb = 0;
    int c = 0;
    char digit[4];
    char key;


    for (int i=0; i<27; i++) {
        head = push(english_letters[i],frequency[i]);
    }

    display();
    read_into_buffer();
    for (int i = 1; i < strlen(buffer); i++) {
        //printf("%c", buffer[i]);
        if (buffer[i] != '\n') {
            counter += 1;
        }
        if (buffer[i] == '\n') {
            if (line_count % 2 == 0) {
                printf("\tKEY\t");
                counter += 1;
                right_bound = left_bound + counter;
                printf("LEFT BOUND = %d\t\t", left_bound);
                    //printf("%c", buffer[j]);
                    key = buffer[left_bound + 1];
                    printf("%c", key);

                printf("\t\tRIGHT BOUND = %d", right_bound);
                putchar('\n');
                left_bound = right_bound;
                counter = 0;
                line_count += 1;
            }
            else {
                printf("\tVALUES\t");
                counter += 1;
                lb = left_bound;
                right_bound = left_bound + counter;
                printf("LEFT BOUND = %d\t\t", left_bound);
                for (int j = left_bound + 1 ; j < right_bound; j++) {
                //    printf("XXXXX: %c", buffer[j-1]);
                //    if (buffer[j] == ',') {
                //        value_index += 1;
                //        printf("\t\tBUFFER J: %d VALUE_INdEX: %d",
                //                    buffer[j-1], value_index);
                //    }
                    if (buffer[j] != ',') {
                        c += 1;
                    }
                    else if (buffer[j] == ',') {
                        c += 1;
                        rb = lb + c;
                        memset(digit, 0, sizeof(digit));
                        for (int k = lb + 1; k < rb; k++) {
                            digit[k - lb + 1] = buffer[k];
                        }
                    //    for (int z = 0; z < 4; z++) {
                       printf("%s", digit);
                    //   memset(digit, 0, sizeof(digit));
                      // }
                       putchar(',');

                        lb = rb;
                        c = 0;
                        value_index += 1;


                    }




                }

                printf("\t\tRIGHT BOUND = %d", right_bound);
                putchar('\n');
                left_bound = right_bound;
                counter = 0;
                line_count +=1;
            }

        }
        //printf("%c", buffer[
    }
        printf("\n\n\\n count = %d\n", line_count);

}
