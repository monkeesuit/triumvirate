#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 500

char *enterfile(void) {
  
  char filename[SIZE];
  char *buffer = malloc( SIZE * sizeof(char*));;
  int i = 0;
  
  
  FILE *file;
  printf("Filename: ");
  fgets(filename, 50, stdin);
  filename[strlen(filename)-1] = '\0';
  
  file = fopen(filename, "r");
  
  if(file != NULL);{
    i = fread(buffer, sizeof(char), SIZE, file);
  }
  
  fclose(file);
  
  return buffer;
}

/*
int main(void) {
  char *data;
  data = enterfile();
  printf("InMain...\t%s\n",data);
}
 */
