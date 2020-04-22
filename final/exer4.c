#include <stdio.h>
#include <string.h>

#define N_ROWS 12
#define N_COLUMNS 15
#define MAX_LINE 1024

int begin_with(char *string1, char *string2);
int my_stringlen(char *str);
int my_strcmp(char *str1, char *str2);
int is_sub_string(char *str1, char *str2);
int remove_char(char str[], char c);
int isAlNum (char c);
void classify (int array[], int n);
int main(int argc, char *argv[]) {
    int array[] = {0, 1, 1, 3 ,2};
    int n = 5;
    classify(array, n);
    return 0;
}
void classify (int array[], int n) {
    int i = 0;
    int num = 0;
    int distance = 0;
    while (i < n) {
        if (array[i] == 0) {
            num++;
        }
        if (num == 1) {
            distance ++;
        }
        i++;
    }
    distance = distance - 1;
    if (num == 0) {
        printf("a\n");
    } else if (num == 1) {
        printf("b\n");
    } else if (distance % 2 == 0) {
        printf("c\n");
    } else {
        printf("d\n");
    }

}
struct node *intersection(struct node *set1, struct node *set2) {
    int i = 0;
    struct node *newhead = malloc(sizeof(struct node));
    newhead->next = NULL;
    new = newhead;
    struct node *cur1 = set1;
    while (cur1 != NULL) {
        struct node *cur2 = set2;
        while (cur2 != NULL) {
            if (cur1->data == cur2->data) {
                
                new->data = cur1->data;
                new->next = malloc(sizeof(struct node));
                new = new->next;
                new->next = NULL;
            }
            cur2 = cur2->next;
        }
        cur1 = cur1->next;
    }
    new = NULL;
    return newhead;
}
/*
int isAlNum (char c) {
    if ((c <= 'z' && c >= 'a') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}
int remove_char(char str[], char c) {
    int i = 0;
    while (i < strlen(str)) {
        if (str[i] == c) {
            str[i] = str[i++];
            while (i < strlen(str) - 2){
                str[i] = str[i++];
                i++;
            }
        return 1;
        }
        i ++;
    }
    return 0;

}

int is_sub_string(char *str1, char *str2){

    if (strlen(str1) >= strlen(str2)) {
        return 0;
    } else {
        int i = 0;
        while (i < strlen(str2) - strlen(str1) + 1) {
            if (strncmp(str1, str2, strlen(str1)) == 0) {
                return 1;
            }
            
            i++;
        }
        return 1;
    }

}

int my_stringlen(char *str) {
    int num = 0;
    int i = 0;
    while (str[i] != '\0') {
        i++;
        num++;
    }
    num --;
    return num;

}

int my_strcmp(char *str1, char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    } else{
        int i = 0;
        while (i < strlen(str1)) {
            if (str1[i] != str2[i]) {
                return 0;
            }
            i++;
        }
        return 1;
    }
}
int identical(struct node *head1, struct node *head2) {
    struct node *cur1 = head1;
    int num1 = 0;
    while (cur1 != NULL) {
        num1 ++;
        cur1 = cur1->next;
    }
    struct node *cur2 = head2;
    int num2 = 0;
    while (cur1 != NULL) {
        num2 ++;
        cur2 = cur2->next;
    }
    if (num1 != num2) {
        return 0;
    } else {
        cur1 = head1;
        cur2 = head2;
        while (cur1 != NULL && cur2 != NULL && cur1->data == cur2->data) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        if (cur1 == NULL && cur2 == NULL) {
            return 1;
        } else {
            return 0;
        }
    }

}

struct node *copy(struct node *head) {
    struct node *c = head;
    if (head == NULL) {
        return NULL;
    }
    struct node *newhead = malloc(sizeof(struct node));
    newhead->data = c->data;
    newhead->next = NULL;
    struct node *last_new = newhead;
    c = c->next;
    while(c != NULL) {
        struct node *newnext = malloc(sizeof(struct node));
        newnext->data = c->data;
        newnext->next = NULL;
        last_new->next = newnext;
        last_new = newnext;
        c = c->next;
    }

    return last_new;
}


int begin_with(char *string1, char *string2) {
    if (strstr(string1, string2) != string1) {
        return 0;
    }
    return 1;
}*/
