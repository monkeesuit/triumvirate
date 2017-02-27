#include 


char  english_letters[27] = {
                            ' ', 'a', 'b', 'c', 'd',
                            'e', 'f', 'g', 'h', 'i',
                            'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's',
                            't', 'u', 'v', 'w', 'x',
                            'y', 'z'
                        	};

int frequency[27] = {
			  	 	19, 7, 1, 2, 4, 
	 		  	 	10,  2, 2, 5, 6, 
			  	 	1, 1, 3, 2, 6, 
			  	 	6, 2, 1, 5, 5, 
	             	7, 2, 1, 2, 1, 
			  	 	2, 1
		    		};


typedef struct KeySpaceElement {
	char key[3];
	int frequency;
	char cipher_characters[60];
   	struct KeySpaceElement * next;
}

KeySpaceElement * head = NULL;
head = malloc(sizeof(KeySpaceElement));
if (head == NULL) {
    return 1;
}

void push(KeySpaceElemnt ** head, char key, int frequency) {
	KeySpaceElement * entry;
    entry = malloc(sizeof(KeySpaceElement));

    entry->key = key;
	entry->frequency = frequency;
    entry->next = *head;
    *head = entry;
}
