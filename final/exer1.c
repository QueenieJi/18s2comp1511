#include <stdio.h>
#include <string.h>
void current_max();
void snap();
void array_snap();
void matrix();
int main () {
    /*int age;
    printf("What is your age?\n");
    scanf("%d", &age);
    if (age >= 16) {
        printf("You can drive!\n");
    } else {
        printf("Go back to school!\n");
    }
    printf("Have a nice day!\n");*/
    //current_max();
    //snap();
    //array_snap();
    //matrix();


    char *s = "hello";
    printf("%d\n", strcmp(s, s));
    return 0;
}
void current_max() {
    int x, currmax, noRead;
    noRead = scanf("%d", &x);
    if (noRead == 1) {
        currmax = x;
    } else {
        printf("Please enter a number!\n");
    }
    while (noRead == 1) {
        if (currmax < x) {
            currmax = x;
        }
        noRead = scanf("%d", &x);
    }
    printf("the current maxmum is %d\n", currmax);
}

void snap () {
    int curr, pre;
    int noRe = scanf("%d", &pre);
    int noRead = scanf("%d", &curr);
    if (noRe != 1) {
        printf("Enter a number!\n");
    }
    while (noRead == 1) {
        if (curr == pre) {
            printf("Snap!\n");
            break;
        } else {
            pre = curr;
            curr = scanf("%d", &curr);
        }
    }
}

void array_snap() {
    int num[10];
    int i = 0;
    int decision = 0;
    while (i < 10) {
        scanf("%d", &num[i]);
        i ++;
    } 
    i = 0;
    while (i < 10) {
        printf("%d,", num[i]);
        i ++;
    } 
    i = 0;
    while (i < 10) {
        int j = i + 1;
        while (j < 10) {
            if (num[i] == num[j]) {
                decision = 1;
                break;
            }
            j++;
        }
        i++;
    }
    if (decision == 1) {
        printf("Snap!\n");
    } else {
        printf("No same number\n");
    }
}

void matrix() {
    int matrix[3][3] = {{1, 2, 3},{ 4, 5, 6}, {7, 8, 9}};
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 3) {
            printf("%d, ",matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}
