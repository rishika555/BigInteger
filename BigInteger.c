#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"
typedef struct node {
    int data;
    struct node* next;
} Node;
typedef struct BigInteger {
    struct node* head;
    int sign;
    int len;
} BigInteger;
BigInteger sub(BigInteger A, BigInteger B);
void insertAtBegin( BigInteger *A, int digit) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    newnode->data = digit;
    if (A->head == NULL) {
        A->head = newnode;
        newnode->next = NULL;
    } else {
        newnode->next = A->head;
        A->head = newnode;
    }
}
BigInteger initialize(char* s) {
    BigInteger A;
    A.head = NULL;
    int i=0;
    if (s[0] == '-') {
        A.sign = -1;
        i++;
    }
    else {
        A.sign = 1;
    }
    while(s[i]=='0') {
        i++;
    }
    while(s[i]!='\0'){
            insertAtBegin(&A, s[i] - '0');
            i++;
        }
        A.len =i;
    return A;
}
struct BigInteger reverse(struct BigInteger A) {
    struct node* current = A.head, *prev = NULL, *temp = NULL;
    while (current != NULL) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    A.head = prev;
    return A;
}
int compare( BigInteger A, BigInteger B) {
    if (A.len > B.len)
        return 1;
    if (A.len < B.len)
        return -1;
    //A = reverse(A);
    //B = reverse(B);
    struct node* num1 = A.head, *num2 = B.head;
    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num1->data < num2->data) {
            return -1;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    return 0;
}
BigInteger add(struct BigInteger A, struct BigInteger B) {
    if (A.sign != B.sign) {
        struct BigInteger result;
        result.sign = -1;
        if (A.sign == -1) {
            A.sign = 1;
            result = sub(B, A);
        }
        else if (B.sign == -1) {
            B.sign = 1;
            result = sub(A, B);
        }
        return result;
    }
    int s = 0, c = 0;
    struct BigInteger sum;
    sum.head = NULL;
    if (A.sign == -1) {
        sum.sign = -1;
    } else {
        sum.sign = 1;
    }
    c = 0;
    struct node* num1 = A.head, *num2 = B.head;
    while (num1 != NULL || num2 != NULL) {
        s = c;
        if (num1 != NULL) {
            s = s + num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            s = s + num2->data;
            num2 = num2->next;
        }
        c = s / 10;
        s = s % 10;
        insertAtBegin(&sum, s);
    }
    if (c != 0) {
        insertAtBegin(&sum, c);
    }
    return sum;
}
void appendNode(struct BigInteger *A, int digit) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (!newnode) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    newnode->data = digit;
    newnode->next = NULL;
    if (A->head == NULL) {
        A->head = newnode;
    } else {
        struct node* cur = A->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newnode;
    }
}
struct BigInteger sub(struct BigInteger A, struct BigInteger B) {
    int d = 0, b = 0;
    struct BigInteger dif;
    dif.head = NULL;

    if (A.sign == -1 && B.sign == -1) {
        if (compare(A, B)) {
            dif.sign = -1;
        } else {
            dif.sign = 1;
        }
    } else if (A.sign == 1 && B.sign == -1) {
        dif.sign = 1;
    } else if (A.sign == -1 && B.sign == 1) {
        dif.sign = -1;
    } else {
        dif.sign = 1;
    }
    struct node* num1 = A.head, *num2 = B.head;
    while (num1 != NULL || num2 != NULL) {
        d = b;
        if (num1 != NULL) {
            d = d + num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            d = d - num2->data;
            num2 = num2->next;
        }
        if (d < 0) {
            d = d + 10;
            b = -1;
        } else {
            b = 0;
        }
        insertAtBegin(&dif, d);
    }
    Node* temp=dif.head;
    while(temp!=NULL) {
        if(temp->data==0) {
            temp=temp->next;
        }
        if(temp->data!=0)
            break;
        temp=temp->next;
    } 
    return dif;
}
struct BigInteger mul(struct BigInteger A, struct BigInteger B) {
    struct BigInteger pro = initialize("0");
    pro.sign = (A.sign == B.sign) ? 1 : -1;

    struct node* num1 = A.head;
    while (num1 != NULL) {
        int p = 0, c = 0;
        struct BigInteger temp = initialize("0");
        struct node* num2 = B.head;

        for (int i = 0; i < num1->data; i++) {
            appendNode(&temp, 0);
        }

        while (num2 != NULL) {
            p = (num1->data) * (num2->data) + c;
            c = p / 10;
            p = p % 10;
            appendNode(&temp, p);
            num2 = num2->next;
        }

        if (c > 0) {
            appendNode(&temp, c);
        }

        pro = add(pro, temp);
        num1 = num1->next;
    }

    return pro;
}
struct BigInteger div1(struct BigInteger A, struct BigInteger B) {
    if (compare(A, B) < 0) {
        struct BigInteger quotient = initialize("0");
        return quotient;
    }

    struct BigInteger quotient = initialize("0");
    struct BigInteger temp = initialize("0");

    struct node* num1 = A.head;

    while (num1 != NULL) {
        temp = mul(temp, initialize("10"));
        appendNode(&temp, num1->data);
        if (compare(temp, B) >= 0) {
            int count = 0;
            while (compare(temp, B) >= 0) {
                temp = sub(temp, B);
                count++;
            }
            appendNode(&quotient, count);
        } else {
            appendNode(&quotient, 0);
        }
        num1 = num1->next;
    }
    return quotient;
}

struct BigInteger mod(struct BigInteger A, struct BigInteger B) {
    struct BigInteger quotient = div1(A, B);
    struct BigInteger product = mul(quotient, B);
    struct BigInteger remainder = sub(A, product);
    return remainder;
}
void displayReverse(struct node* current) {
    if (current == NULL) {
        return;
    }
    displayReverse(current->next);
    printf("%d", current->data);
}

void display(struct BigInteger A) {
    if (A.head == NULL) {
        printf("Big Integer is Empty.\n");
        return;
    }
    if (A.sign == -1) {
        printf("-");
    }
    struct node* n=A.head;
    while(n!=NULL) {
        printf("%d",n->data);
        n=n->next;
    }
    //displayReverse(A.head);
    printf("\n");
}
