#include <stdio.h>
#include<stdilo.h>


struct node{
	int value;
	struct node *next;
}

void print(struct node *head);

int main (int argc, char const *argv[]){
	struct node *list1 = maloc (sizeof(struct node));
	list1->next = NULL;
	list1->value = 1;
	
	list1->next = maloc (sizeof(struct node));
	list1->next->next = NULL;
	list1->next->next->value = 3;
	
	list1->next->next = maloc (sizeof(struct node));
	list1->next->next->next = NULL;
	list1->next->next->value = 4;
	
	print(list1);
	return 0;
}

struct node *list_append(struct node list1, struct node list2){

	
	if (list1 == NULL) {
		return list2;
	}else if (list2 == NULL) {
		return list1;
	}
		struct node *curr = list1;
		while (curr->next != NULL) {
			curr = curr->next;
	
		}
		curr->next = list2;
		
		return list1;
}

void print(struct node *head) {
	if(head == NULL) {
		printf("X\n");
		return;
	} else {
		printf("%d",head->next);
		print(head);
	}
}

