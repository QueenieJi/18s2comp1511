
// Test file to test the function "arrayPositiveMin".
// 

#include <stdio.h>
#include <math.h>

int arrayPositiveMin(int a[], int size);


void checkArrayPositiveMin(int test_no, int a[], int size, int expected_answer) {

    int student_answer = arrayPositiveMin(a, size);
    
    printf("------------- \n");
    if (student_answer == expected_answer) {
        printf("Test %d Passed\n\n", test_no );
        return ;
    }
    
    printf("Test %d Failed!, see below for the expected answer.\n", test_no);
    int i = 0;
    printf("  Array is: ");
    while (i < size) {
        printf("%d, ", a[i]);
        i++; 
    }
    printf("\n");
    printf("  Average Positive Min, expected: %d, your answer: %d\n\n", expected_answer, student_answer);

}

int main(int argc, char *argv[]) {
 
    int a1[]  = {4, 2, 9};
    checkArrayPositiveMin(1, a1, 3, 2); 
    
    int a2[]  = {5, -6, 3 , 20};
    checkArrayPositiveMin(2, a2, 4, 3);     
    
    int a3[]  = {-5, 6, -12 , 5, 0, -2 , 8};
    checkArrayPositiveMin(3, a3, 7, 5);   
        
    // Add more test cases here ... 


    return 0;
}


