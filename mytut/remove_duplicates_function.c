#include <stdio.h>

int remove_duplicates(int length, int source[],int destination[]);

int main() {
    int test_array[6] = {1, 1, 2, 3, 4, 2};
    int destination[6] = {0};
    printf("%d\n",remove_duplicates(6, test_array, destination));
    return 0;
}
int remove_duplicates(int length, int source[],int destination[]) {
    int i = 0;
    int new_len = length;
    
    while (i < length) {
        int j = 0;
        while (j < i) {
            if (source[i] == source[j]) {
                new_len--;
            }
            j++;
        } 
        
        i++;
    }
    return new_len;

}
