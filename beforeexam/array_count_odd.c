#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 1024

int count_odd(int length, int array[]);
int main () {

    int array[MAX_NUM];
    int i = 0;
    int len = 0;
    int noRead = scanf("%d", &array[0]);
    while (noRead != 0) {
        i++;
        scanf("%d", &array[i]);
        len++;
        noRead = scanf("%d", &array[i]);
    }
    
    int num = count_odd(len, array);
    printf("%d", num);
    return 0;
}
int count_odd(int length, int array[]) {
    int num = 0;
    int i = 0;
    while (i < length) {
        if (array[i] % 2 != 0) {
            num++;
        }
        i++;
    
    }
    return num;
}
