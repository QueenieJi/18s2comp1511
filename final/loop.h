#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int val;
};

int hasloop(struct node *first);
struct node *createNode(int val);
struct node *append(struct node *first, int val);
void deletelist(struct node *first);
