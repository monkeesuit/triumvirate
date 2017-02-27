struct KeySpaceElement {
	char key;
	int frequency;
	char cipher_characters[60];
	struct KeySpaceElement *next;
};  

struct KeySpaceElement *head = NULL;

void push(char key, int frequency) {
	struct KeySpaceElement *entry;
	entry = malloc(sizeof(struct KeySpaceElement));
	
	entry->key = key;
	entry->frequency = frequency;
	entry->next = head;
	head = entry;
}

void display() {
	struct KeySpaceElement *entry = head;
	
	while(entry != NULL) {
		printf("(%c,%d)", entry->key, entry->frequency);
		entry = entry->next;
	}
}
