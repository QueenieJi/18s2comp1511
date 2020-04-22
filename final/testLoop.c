#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "loop.h"

//Tests for qc created by Mitchell Shelton
//Do not edit this file

void runtests();

int main(void) {

    runtests();
    return 0;

}

void runtests() {

    struct node *first = NULL;
    printf("===Test 1: Checking NULL list===\n");
    printf("List: X\n");
    assert(hasloop(first) == 0);
    printf("===Test 1 Passed===\n");
    first = append(first, 5);
    printf("===Test 2: one element, no loop===\n");
    printf("List: 5->X\n");
    assert(hasloop(first) == 0);
    printf("===Test 2:  Passed===\n");
    first->next = first;
    printf("===Test 3: one element, has loop===\n");
    printf("List: 5->5\n");
    assert(hasloop(first) == 1);
    printf("===Test 3:  Passed===\n");
    first->next = NULL;
    
    first = append(first, 1);
    first = append(first, 3);
    first = append(first, 7);

    printf("===Test 4: 4 elements, no loop===\n");
    printf("List: 5->1->3->7->X\n");
    assert(hasloop(first) == 0);
    printf("===Test 4:  Passed===\n");

    first->next->next->next->next = first;
    printf("===Test 5: 4 elements, has loop===\n");
    printf("List: 5->1->3->7->5\n");
    assert(hasloop(first) == 1);
    printf("===Test 5:  Passed===\n");

    first->next->next->next->next = first->next;
    printf("===Test 6: 4 elements, has loop===\n");
    printf("List: 5->1->3->7->1\n");
    assert(hasloop(first) == 1);
    printf("===Test 6:  Passed===\n");

    first->next->next->next->next = first->next->next;
    printf("===Test 7: 4 elements, has loop===\n");
    printf("List: 5->1->3->7->3\n");
    assert(hasloop(first) == 1);
    printf("===Test 7:  Passed===\n");

    first->next->next->next->next = first->next->next->next;
    printf("===Test 8: 4 elements, has loop===\n");
    printf("List: 5->1->3->7->7\n");
    assert(hasloop(first) == 1);
    printf("===Test 8:  Passed===\n");

    first->next->next->next->next = NULL;
    first = append(first, 1);
    first->next->next->next->next->next = first->next;
    printf("===Test 9: 5 elements, has loop, sneaky duplicate values===\n");
    printf("List: 5->1->3->7->1->1\n");
    assert(hasloop(first) == 1);
    printf("===Test 9:  Passed===\n");

 
    

    first->next->next->next->next->next = NULL;
    deletelist(first);

    

}