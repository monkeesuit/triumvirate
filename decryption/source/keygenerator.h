typedef struct KeySpaceElement {
	char key[3];
    	int frequency;
	char cipher_characters[60];
    	struct KeySpaceElement * next;
}
