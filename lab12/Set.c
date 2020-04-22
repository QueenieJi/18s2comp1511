#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define a new `Set` type.
typedef struct _set {
    struct _node *head;
}*Set;

typedef struct _node {
    int item;
    struct _node *next;
} *Node;

// Define an `item` type.  `Set` manipulates `item`s.
typedef int item;

bool setContains(Set s, item item);

// Create a new `Set`.
Set newSet(void) {
    Set new = malloc(sizeof(struct _set));
    new->head = NULL;
    return new;
}

Node newNode(int item) {
    Node new = malloc(sizeof(struct _node));
    new->next = NULL;
    new->item = item;
    return new;
}

// Release all resources associated with a `Set`.
void destroySet(Set set) {
    Node cur = set->head;
    while (cur != NULL) {
        Node tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(set);
}

// Add an `item` to the `Set`.
void setAdd(Set s, item item) {
    if (setContains(s, item)) return;
    
    Node new = newNode(item);
    new->next = s->head;
    s->head = new;
}

// Remove an `item` from the `Set`.
void setRemove(Set s, item item) {
    Node curr = s->head;
    Node prev = NULL;
    while(curr != NULL && curr->item != item) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != NULL && curr->item == item) {
        if (prev == NULL) {
            s->head = curr->next;
            free(curr);
        } else {
            prev->next = curr->next;
            free(curr);
        }
    }
}

// Does the `Set` contain this `item`?
bool setContains(Set s, item item) {
    Node curr = s->head;
    while (curr != NULL) {
        if (curr->item == item) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// How many items are in the `Set`?
int setSize(Set s) {
    Node curr = s->head;
    int counter = 0;
    while (curr != NULL) {
        counter++;
        curr = curr->next;
    }
    return counter;
}

// Take the union of two sets(a â?ª b).
Set setUnion(Set a, Set b) {
    Set un = newSet();
    Node cur_a = a->head;
    Node cur_b = b->head;
    while (cur_a != NULL) {
        setAdd(un, cur_a->item);
        cur_a = cur_a->next;
    }
    while (cur_b != NULL) {
        if (setContains(a, cur_b->item) == false) {
            setAdd(un, cur_b->item);
        }
        cur_b = cur_b->next;
    }
    return un; 
}

// Take the intersection of two sets(a â?© b).
Set setIntersection(Set a, Set b) {
    Set in = newSet();
    Node cur_a = a->head;
    while (cur_a != NULL) {
        if (setContains(b, cur_a->item)) {
            setAdd(in, cur_a->item);
        }
        cur_a = cur_a->next;
    }
    return in;
}

// Is `a` a subset of `b`(a â?? b)?
bool setSubset(Set a, Set b) {
    Node cur = a->head;
    while (cur != NULL) {
        if (setContains(b, cur->item) == false) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

// Is `a` equal to `b`(where a â?? b and b â?? a, a == b).
bool setEqual(Set a, Set b) {
    return setSubset(a, b) && setSubset(b, a);
}


