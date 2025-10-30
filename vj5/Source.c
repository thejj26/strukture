#define _CRT_SECURE_NO_WARNINGS

#define FILE_ERROR -1
#define MALLOC_ERROR -2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct n
{
	int num;
	struct n *next;
} number;

// pusha u stack
int push(int, number *);

// poppa iz stacka
int pop(number *);

// odraduje trazenu operaciju
int calc(int, int, char);

// kalkulira postfix dok ga cita iz dadtoteke
int loadAndCalc(char *, number *);

int main()
{
	int result = 0; // rezultat izraza

	number head = {0, NULL}; // stack brojeva

	result = loadAndCalc("input.txt", &head);

	printf("Rezultat je %d\n", result);

	return 0;
}


int push(int num, number *p)
{
	number *new = (number *)malloc(sizeof(number));
	if (new == NULL)
		return MALLOC_ERROR;

	new->num = num;
	new->next = p->next;
	p->next = new;

	return EXIT_SUCCESS;
}

int pop(number *p)
{
	number *temp = p->next;
	if (temp == NULL)
		return EXIT_FAILURE;

	int n = temp->num;

	p->next = temp->next;
	free(temp);
	return n;
}

int calc(int a, int b, char o)
{
	int res = 0;
	switch (o)
	{
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
		res = a * b;
		break;
	case '/':
		res = a / b;
		break;
	}

	return res;
}

int loadAndCalc(char *path, number *p)
{
	char buffer[10], *end;	//buffer sprema trenutno procitani string, end je potreban za strtol
	int a = 0, b = 0;

	FILE *f = fopen(path, "r");
	if (f == NULL)
		return FILE_ERROR;

	while (!feof(f))
	{
		fscanf(f, "%s ", buffer);

		switch (buffer[0])
		{
		case '+':
		case '-':
		case '*':
		case '/':	//ukoliko je procitana operacija
			b = pop(p);	//dohvaca brojeve
			a = pop(p);	//obrnut redoslijed jer se tako spremaju u stack (noviji izlazi prvi)
			push(calc(a, b, buffer[0]), p);	//rezultat operacije sprema natrag u stack
			break;
		default:
			push(strtol(buffer, &end, 10), p);	//pusha novi broj u stack
		}
	}

	fclose(f);
	return pop(p);	//vraca rezultat
}