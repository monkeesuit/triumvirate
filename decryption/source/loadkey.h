#ifndef LOAD_KEY_H
#define LOAD_KEY_H

#define SIZE 500

char data[SIZE];
int read_in_data();

struct KeySpaceElement {
  char key;
  int frequency;
  int remaining;
  char values[60];
  struct KeySpaceElement *next;
};

struct KeySpaceElement *initializekey(struct KeySpaceElement *head, char key, int frequency);
struct KeySpaceElement *loadkey(struct KeySpaceElement *head, char *data);
void displaykey(struct KeySpaceElement *head);

#endif
