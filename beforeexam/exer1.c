#include <stdio.h>

#define FIRST_NUMBER     10
#define SECOND_NUMBER    20
#define TOTAL   FIRST_NUMBER + SECOND_NUMBER
#define AVERAGE TOTAL / 2

int main(void) {
    int row, column;
    printf("Enter row number: ");
    scanf("%d", &row);
    printf("Enter column number: ");
    scanf("%d", &column);
    int i = 0;
    while (i < row) {
        int j = 0;
        while (j < column) {
            if (j == 0 || j == column - 1) {
                printf("*");
            } else if (i == 0 || i == row - 1) {
                printf("*");
            } else {
                printf(" ");
            }
            j++;
        }
        printf("\n");
        i++;
    }
    return 0;
}
