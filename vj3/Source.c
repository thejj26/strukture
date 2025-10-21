#define _CRT_SECURE_NO_WARNINGS
#define EMPTY_LIST -1
#define MALLOC_ERROR -2
#define NOT_FOUND -3
#define FILE_ERROR -4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {	//struktura person
	char* f_name;
	char* l_name;
	int year;

	struct Person* next;	//pointer na iducu osobu u listi
};

typedef struct Person person;
person* addFirst(char*, char*, int, person*);	//dodaje novu osobu na start
int printList(person*);	//ispisuje sve clanove
person* addLast(char*, char*, int, person*);	//dodaje novu osobu na kraj
person* find(char*, person*);	//pronalazi osobu po prezimenu
person* findPrev(char*, person*);	//pronalazi osobu prije trazene po prezimenu
int delete(char*, person*);	//brise osobu po prezimenu

//vj3
person* addAfter(char*, char*, int, char*, person*);	//dodaje osobu nakon odabrane
person* addBefore(char*, char*, int, char*, person*);	//dodaje osobu prije odabrane
int outputList(char*, person*);	//osobe dodaje u file
person* inputList(char*, person*);	//osobe ucitaje iz filea
	
int main() {
	int err_handler = 0;	//za lakse spremanje return vrijednosti

	person head = { "", "", 0 , NULL};	//head element liste

	inputList("input.txt", &head);
	printList(head.next);

	free(&head);
	return 0;
}

person* addFirst(char* fname, char* lname, int year, person* p) {
	person* new = (person*)malloc(sizeof(person));	//alociranje nove osobe
	if (!new) return MALLOC_ERROR;

	new->f_name = fname;
	new->l_name = lname;
	new->year = year;
	new->next = p->next;

	p->next = new;	//postavljanje na pocetak

	return new;
}

int printList(person* p) {
	while (p) {	//sve dok je valjani clan(adresa nije null)
		printf("%s %s %d\n", p->f_name, p->l_name, p->year);
		p = p->next;	//prelazak na iduci clan
	}

	return 0;
}

person* addLast(char* fname, char* lname, int year, person* p) {
	while (p->next) {	//pronalazi zadnji clan
		p = p->next;
	}

	person* new=addFirst(fname, lname, year, p); //p je sada zadnji clan pa dodaje na kraj
	if (new == NULL) return MALLOC_ERROR;

	return new;
}

person* find(char* lname, person* p) {
	while (p) {
		if (!strcmp(p->l_name, lname)) break;	//usporeduje stringove, ako su jednaki prekida petlju
		p = p->next;
	}

	return p;
}

person* findPrev(char* lname, person* p) {
	if (p == NULL) return NULL;	//ako nema elemenata
	while (p->next) {
		if (!strcmp(p->next->l_name, lname)) break;
		p = p->next;
	}

	return p;
}

int delete(char* lname, person* p) {
	p = findPrev(lname, p);
	if (p==NULL || p->next==NULL) return EMPTY_LIST; //ukoliko nema elemenata

	person* temp = p->next;
	p->next = temp->next;
	free(temp);

	return 0;
}

person* addAfter(char* fname, char* lname, int year, char* _lname, person* p) {
	p = find(_lname, p);
	if (p == NULL) return NOT_FOUND;

	person* new = addFirst(fname, lname, year, p);
	if (new == NULL) return MALLOC_ERROR;

	return new;
}

person* addBefore(char* fname, char* lname, int year, char* _lname, person* p) {
	p = findPrev(_lname, p);
	if (p == NULL) return NOT_FOUND;

	person* new = addFirst(fname, lname, year, p);
	if (new == NULL) return MALLOC_ERROR;

	return new;
}

int outputList(char* path, person* p) {
	FILE* f = fopen(path, "w");
	if (f == NULL) return FILE_ERROR;

	while (p) {
		fprintf(f, "%s %s %d\n", p->f_name, p->l_name, p->year);
		p = p->next;
	}

	fclose(f);
	return 0;
}

person* inputList(char* path, person* p) {
	FILE* f = fopen(path, "r");
	if (f == NULL) return FILE_ERROR;

	char* fname;
	char* lname;
	int year;

	while (!feof(f)) {
		fscanf(f, "%s %s %d\n", fname, lname, &year);
		addLast(fname, lname, year, p);
	}

	fclose(f);
	return 0;
}
