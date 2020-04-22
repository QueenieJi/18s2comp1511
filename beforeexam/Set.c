// COMP1511 18s2 -- a Set ADT
// Don't modify this file!

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Set.h"

struct node {
    struct node *next;
    int data;
};

// Define a new `Set` type.
typedef struct _set {
    struct node *set1;
}*Set;

// Define an `item` type.  `Set` manipulates `item`s.
typedef int item;

// Create a new `Set`.
Set newSet(void) {
    Set newSet = malloc(sizeof(struct _set));
    newSet->set1  = NULL;
    return newSet;

}
// Does the `Set` contain this `item`?
bool setContains(Set s, item item) {
    struct node *cur = s->set1;
    while (cur != NULL) {
        if (cur->data == item) {
            return true;
        }
        cur = cur->next;
    }
    return false;
    
}

// Release all resources associated with a `Set`.
void destroySet(Set s) {
    struct node *destroy = s->set1;
    while (destroy != NULL) {
        struct node *temp = destroy;
        destroy = destroy->next;
        free(temp);
    }
    //free(s->set2);
    free(s);
}

// Add an `item` to the `Set`.
void setAdd(Set s, item item) {
    if (setContains(s, item)) {
        return;
    }
    struct node *new = malloc(sizeof(struct node));
    new->data = item;
    new->next = s->set1;
    s->set1 = new;
}

// Remove an `item` from the `Set`.
void setRemove(Set s, item item) {
    if (s->set1 == NULL) {
        return;
    }
    struct node *cur = s->set1;
    struct node *prev = NULL;
    while (cur != NULL) {
        if (cur->data == item) {
            if (prev == NULL) {
                s->set1 = s->set1->next;
                cur = s->set1;
            } else {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
            }
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

}


// How many items are in the `Set`?
int setSize(Set s) {
    struct node *cur = s->set1;
    int count = 0;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

// Take the union of two sets(a â?ª b).
Set setUnion(Set a, Set b) {
    Set new = newSet();
    struct node *seta = a->set1;
    struct node *setb = b->set1;
    while (seta != NULL) {
        setAdd(new, seta->data);
        seta = seta->next;
    }
    while (setb != NULL) {
        setAdd(new, setb->data);
        setb = setb->next;
    }
    return new;
}

// Take the intersection of two sets(a â?© b).
Set setIntersection(Set a, Set b) {
    Set new = newSet();
    new->set1 = a->set1;
    struct node *cur = b->set1;
    while (cur != NULL) {
        if (setContains(b, cur->data) == 0) {
            setRemove(new, cur->data);
        }
        cur = cur->next;
    }
    return new;
}

// Is `a` a subset of `b`(a â?? b)?
bool setSubset(Set a, Set b) {
    struct node *cur = a->set1;
    while (cur != NULL) {
        if (setContains(b, cur->data) == 0) {
            return 0;
        }
        cur = cur->next;
    }
    return 1;
}

// Is `a` equal to `b`(where a â?? b and b â?? a, a == b).
bool setEqual(Set a, Set b) {
    if(setSubset(a, b) && setSubset(b, a)) {
        return true;
    }
    return false;
}

