#include <stdio.h>

void change_to_upper();
void shift(int num);
int main(int argc, char *argv[]) {
    double a = (int)1.0/2;
    double b = 1/2;
    printf("b: %lf\n",b);
    printf("a: %lf",a);
    //change_to_upper();
    return 0;
}
void change_to_upper() {
    int c;
    c = getchar();
    int string[1000000] = {0};
    int i = 0;
    while (c != EOF) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        string[i] = c;
        i++;
        c = getchar();
    }
    int j = 0;
    while (j < i) {
        printf("%c", string[j]);
        j++;
    }
}
