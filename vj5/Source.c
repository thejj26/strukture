#define _CRT_SECURE_NO_WARNINGS

#define FILE_ERROR -1
#define MALLOC_ERROR -2
#define END '\0'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct o {
	char op;
	struct o* next;
};

struct n {
	int num;
	struct n* next;
};

typedef struct o operand; 
typedef struct n number;

//pushaju u stack
int pushOperand(char, operand*);
int pushNumber(int, number*);

//poppaju iz stacka
char popOperand(operand*);
int popNumber(number*);

//odraduje trazenu operaciju
int calc(int, int, char);

//kalkulira postfix
int calcPostfix(operand*, number*);

int main() {
	int result = 0;	//rezultat izraza

	operand o_head = { 0, NULL };	//stack operatora
	number n_head = { 0, NULL };	//stack brojeva
	loadPostfix("input.txt", &o_head, &n_head);

	result = calcPostfix(&o_head, &n_head);

	printf("Rezultat je %d\n", result);

	return 0;
}

int pushOperand(char op, operand* p) {
	operand* new = (operand*)malloc(sizeof(operand));
	if(new==NULL){
		free(new);
		return MALLOC_ERROR;
	}

	new->op = op;
	new->next = p->next;
	p->next = new;

	return EXIT_SUCCESS;
}

int pushNumber(int num, number* p) {
	number* new = (number*)malloc(sizeof(number));
	if (new == NULL) {
		free(new);
		return MALLOC_ERROR;
	}

	new->num = num;
	new->next = p->next;
	p->next = new;

	return EXIT_SUCCESS;
}

char popOperand(operand* p) {
	operand* temp = p->next;
	if (temp == NULL) return END;

	char c=temp->op;

	p->next = temp->next;
	free(temp);
	return c;
}

int popNumber(number* p) {
	number* temp = p->next;
	if (temp == NULL) return END;

	int n = temp->num;

	p->next = temp->next;
	free(temp);
	return n;
}

int loadPostfix(char* path, operand* o_p, number* n_p) {
	char buffer[10];
	char* end;

	FILE* f = fopen(path, "r");
	if (f == NULL) {
		fclose(f);
		return FILE_ERROR;
	}

	while (!feof(f)) {
		fscanf(f, "%s ", buffer);
		switch (buffer[0]) {
		case '+':
		case '-':
		case '*':
		case '/':
			pushOperand(buffer[0],o_p);
			break;
		default:
			pushNumber(strtol(buffer, &end, 10), n_p);
		}
	}

	free(f);
	return 0;
}

int calc(int a, int b, char o) {
	int res = 0;
	switch (o) {
	case '+':
		res =a + b;
		break;
	case '-':
		res= a - b;
		break;
	case '*':
		res= a * b;
		break;
	case '/':
		res = a / b;
		break;
	}
	
	return res;
}

int calcPostfix(operand* o, number* n) {
	char op = '0';
	int a = 0, b = 0;
	while (1) {
		op = popOperand(o);
		if (op == END) break;
		a = popNumber(n);
		b = popNumber(n);
		pushNumber(calc(a, b, op), n);
	}

	return popNumber(n);
}