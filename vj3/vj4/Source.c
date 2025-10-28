/*FILE
C1 E1 C2 E2...
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR -1
#define FILE_ERROR -2

typedef struct p {
	int c;
	int ex;
	struct p* next;
} pol;

int addSorted(int, int, pol*);	//dodaje polinom, sortira po velicini (silazno)
int loadFromFile(char*, pol*, pol*);	//ucitava polinome iz filea u liste
int add(pol*, pol*, pol*);	//zbrajanje
int mul(pol*, pol*, pol*);	//mnozenje

int main() {

	pol head1 = { 0,0,NULL };
	pol head2 = { 0,0,NULL };
	pol head_result = { 0,0,NULL };

	pol* p = head1.next;

	loadFromFile("input.txt", &head1, &head2);

	while (p != NULL) { 
		printf("%dx^%d \n", p->c, p->ex);
		p = p->next;
	}

	return 0;
}

int addSorted(int coef, int exp, pol* p) {
	pol* new = (pol*)malloc(sizeof(pol));	//novi polinom
	if (new == NULL) return MALLOC_ERROR;	//memory check

	new->c = coef;	//pridrucuje vrijednosti
	new->ex = exp;

	while (p->next != NULL && p->next->ex >= exp) {	//sve dok nije zadnji ili je eksponent veci
		if (p->next->ex == exp) {	//zbraja koeficijente ukoliko su ekspntenti jednaki
			p->next->c += coef;
			free(new);
			return 0;
		}
		p = p->next;
	}

	new->next = p->next;	//dodaje polinom na pripadajuce mjesto
	p->next = new;

	return 0;
}
int loadFromFile(char* path, pol* p1, pol* p2) {
	FILE* f = fopen(path, "r");	//otvara file
	if (f == NULL) { //gleda je li file ispravno otvoren
		fclose(f);
		return FILE_ERROR; 
	}

	char buffer = '0';	//provjerava jesmo li dosli do kraja ili drugog polinoma
	int _c=0, _ex=0;	//temp vrijednosti

	while (buffer != '\n') {	//dok ne dodemo do iducega reda
		fscanf(f, "%d %d", &_c, &_ex);	//cita vrijednosti
		addSorted(_c, _ex, p1);	//unosi u listu
		buffer=fgetc(f);	//provjerava iduci znak
	}
	buffer = '0';

	while (buffer != '\n' || buffer!=EOF) {	//prelazi se na drugu listu, moguc je na kraju EOF
		fscanf(f, "%d %d", &_c, &_ex);
		addSorted(_c, _ex, p2);
		buffer = fgetc(f);
	}

	fclose(f);
	return 0;
}