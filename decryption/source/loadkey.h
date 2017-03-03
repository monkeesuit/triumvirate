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

struct KeySpaceElement *push(struct KeySpaceElement *head, char key, int frequency);
struct KeySpaceElement *parse_data(struct KeySpaceElement *head, char *data);
void display(struct KeySpaceElement *head);

#endif
