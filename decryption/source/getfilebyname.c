#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    char buffer[500];
    char buffer2[500];

    FILE *fp;
    printf("Enter file name: ");
    fgets(buffer, 20, stdin);
    buffer[strlen(buffer)-1] = '\0';

    printf("%s\n", buffer);

    fp = fopen(buffer, "r");

    if (fgets(buffer2, 60, fp) != NULL) {
        buffer2[strlen(buffer2)-1] = '\0';
        puts(buffer2);
    }
    fclose(fp);

    return 0;
}
