#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
	int data;
	struct node* next;
}
struct BigInteger {
	int len;
	int sign;
	struct node* head;
};
struct BigInteger sub(struct BigInteger A, struct BigInteger B);
struct BigInteger* initialise(char* s);
struct BigInteger add(struct BigInteger A, struct BigInteger B);
struct BigInteger mul(struct BigInteger A, struct BigInteger B);
struct BigInteger div1(struct BigInteger A, struct BigInteger B);
struct BigInteger mod(struct BigInteger A, struct BigInteger B);
void display(struct BigInteger A) ;
#endif
