#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
}; 

struct number {
	int x;
	int y;
};

struct node *last_to_first (struct node *head);
struct node *upsidedown (struct node *head);
struct node *free_bigger(struct node *head,int item);
int num_1st(int n_count,struct number n_1st[n_count]);
void quadrant_count(int n_count,struct number n[n_count],int *first,int *third);
int proper(struct node *head, int item);

int main() {
	struct node *a = malloc(sizeof(struct node));
	struct node *b = malloc(sizeof(struct node));
	struct node *c = malloc(sizeof(struct node));
	a->data = 1;
	a->next = b;
	b->data = 2;
	b->next = c;
	c->data = 3;
	c->next = NULL;
	
	int it = proper(a,1);
	printf(" the proper number is %d\n",it);
	/*struct node *creat ;
	
	if (creat == NULL) {
		printf("NOT EXIST");
	}
	while (creat != NULL) {
		printf("%d ",creat->data);
		creat = creat->next;
	}*/
	
	struct number item[5];
	int i = 0;
	while (i < 5) {
		item[i].x = -2 + i;
		item[i].y = -2 - i;
		printf("(%d,%d)",item[i].x,item[i].y);
		i++;
	}
	int count =  num_1st(5,item);
	printf("\n%d\n",count);
	
	int first;
	int third;
	quadrant_count(5,item,&first,&third);
	printf("first quadrant has %d,third quadrant has %d\n",first,third);
	return 0;
}

struct node *last_to_first (struct node *head) {
	if (head == NULL) {
		return NULL;
	}
	if (head != NULL && head->next == NULL) {
		return head;	
	}
	struct node *new = malloc(sizeof(struct node));
	struct node *cur = head;
	struct node *temp = cur->next;
	//0 1 2 3 x
	//	  ^
	//      ^
	while (cur != NULL && temp->next != NULL) {
		cur = cur->next;
		temp = temp->next;
	}
	new->data = temp->data;
	new->next = head;
	cur->next = NULL;
	head = new;
	free(temp);
	return head;
}

struct node *upsidedown(struct node *head) {
	if (head == NULL) {
		return NULL;
	} else if (head->next == NULL) {
		return head;
	}
	struct node *new = malloc(sizeof(struct node));
	new->data = head->data;
	new->next = NULL;
	struct node *cur = head->next;
	while (cur != NULL) {
		struct node *temp = malloc(sizeof(struct node));
		temp->data = cur->data;
		temp->next = new;
		new = temp;
		cur = cur->next;
	}
	return new;
}

struct node *free_bigger(struct node *head,int item){
	if (head == NULL) {
		return NULL;
	}
	while (head != NULL && head->data > item) {
		head = head->next;
	}
	if (head == NULL) {
		return NULL;
	}
	struct node *cur = head;
	while (cur != NULL && cur->next != NULL) {
		struct node *temp = cur->next;
		if (temp->data > item) {
			cur->next = temp->next;
			free(temp);
		}else {		
			cur = cur ->next;
		}
	}
	return head;
}

int num_1st(int n_count,struct number n_1st[n_count]) {
	int i = 0;
	int count = 0;
	while (i < n_count) {
		if(n_1st[i].x > 0 && n_1st[i].y > 0) {
			count++;
		}
		i++;
	}

	return count;
}

void quadrant_count(int n_count,struct number n[n_count],int *first,int *third){
	int i = 0;
	int fir = 0;
	int thir = 0;
	while (i < n_count) {
		if( n[i].x > 0 && n[i].y > 0) {
			fir ++;
		} else if (n[i].x < 0 && n[i].y < 0) {
			thir ++;
		}
		i++;
	}
	*first = fir;
	*third = thir;
}

int proper(struct node *head, int item) {
	if (head == NULL) {
		return 0;
	}
	int count = 0;
	struct node *cur = head;
	while (cur != NULL) {
		if (cur->data >= item) {
			count++;
		}
		cur = cur->next;
	}
	return count;
}
