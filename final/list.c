#include <stdio.h>
#include <stdlib.h>
struct node {
	struct node *next;
	int data;
};

int main () {
    int size;
    scanf("%d", &size);

	int c;
	scanf("%d", &c);
	struct node *head = malloc(sizeof(struct node));
	head->data = c;
	head->next = NULL;
	struct node *tail = head;
	int i = 0;
	while (scanf("%d", &c) == 1 && i < size - 1) {
		struct node *n = malloc(sizeof(struct node));
		n->data = c;
		n->next = NULL;
		tail->next = n;
		tail = n;
		i++;
	}
	printf("[");
	while (head != NULL) {
		printf("%d, ", head->data);
		head = head->next;
	}
	printf("]");
	return 0;
} 
