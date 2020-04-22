#include <stdio.h>
#define MAX 100000

int main() {
    int n;
    int array[MAX][2] = {{0,0}};
    int i = 0;
    while(scanf("%d",&n) == 1) {
        int j = 0;
        while (j < i) {
            if (array[j][0] == n) {
                array[j][1]++;
            }
            
            j++;
        }
        if(j == i) {
            array[i][0] = n;
            array[i][1]++;
            i++;
        }
    }
    
    int result = array[0][1];
    int num = array[0][0];
    int k = 0;
    while (k < i) {
        if(array[k][1] > result) {
            result = array[k][1];
            num = array[k][0];
        }
        k++;
    }
    printf("%d\n",num);
    return 0;
}



