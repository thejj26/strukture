#define _CRT_SECURE_NO_WARNINGS
#define MALLOC_ERROR -1
#define NOT_FOUND -2
#define FILE_ERROR -3

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
int addFirst(char*, char*, int, person*);	//dodaje novu osobu na start
int printList(person*);	//ispisuje sve clanove
int addLast(char*, char*, int, person*);	//dodaje novu osobu na kraj
person* find(char*, person*);	//pronalazi osobu po prezimenu
person* findPrev(char*, person*);	//pronalazi osobu prije trazene po prezimenu
int delete(char*, person*);	//brise osobu po prezimenu

//vj3
int addAfter(char*, char*, int, char*, person*);	//dodaje osobu nakon odabrane
int addBefore(char*, char*, int, char*, person*);	//dodaje osobu prije odabrane
int outputList(char*, person*);	//osobe dodaje u file
int inputList(char*, person*);	//osobe ucitaje iz filea
	
int main() {
	person head = { "", "", 0 , NULL};	//head element liste

	inputList("input.txt", &head);
	outputList("output.txt", head.next);

	return 0;
}

int addFirst(char* fname, char* lname, int year, person* p) {
	person* new = (person*)malloc(sizeof(person));	//alociranje nove osobe
	if (!new) return MALLOC_ERROR;

	new->f_name =strdup(fname);
	new->l_name = strdup(lname);
	new->year = year;
	new->next = p->next;

	p->next = new;	//postavljanje na pocetak

	return 0;
}

int printList(person* p) {
	while (p) {	//sve dok je valjani clan(adresa nije null)
		printf("%s %s %d\n", p->f_name, p->l_name, p->year);
		p = p->next;	//prelazak na iduci clan
	}

	return 0;
}

int addLast(char* fname, char* lname, int year, person* p) {
	while (p->next) {	//pronalazi zadnji clan
		p = p->next;
	}

	return addFirst(fname, lname, year, p); //p je sada zadnji clan pa dodaje na kraj
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
	if (p==NULL || p->next==NULL) return NOT_FOUND; //ukoliko nema elemenata

	person* temp = p->next;
	p->next = temp->next;
	free(temp);

	return 0;
}

int addAfter(char* fname, char* lname, int year, char* _lname, person* p) {
	p = find(_lname, p);
	if (p == NULL) return NOT_FOUND;

	return addFirst(fname, lname, year, p);
}

int addBefore(char* fname, char* lname, int year, char* _lname, person* p) {
	p = findPrev(_lname, p);
	if (p == NULL) return NOT_FOUND;

	return addFirst(fname, lname, year, p);
}

int outputList(char* path, person* p) {
	FILE* f = fopen(path, "w");	//otvara file
	if (f == NULL) return FILE_ERROR;	//provjera je li file otvoren

	while (p) {	//za svaki element liste
		fprintf(f, "%s %s %d\n", p->f_name, p->l_name, p->year);	//ispisuje u file
		p = p->next;
	}

	fclose(f);
	return 0;
}

int inputList(char* path, person* p) {
	int err=0;	//error handling

	FILE* f = fopen(path, "r");
	if (f == NULL) return FILE_ERROR;

	char fname[20];	//spremaju podatke
	char lname[20];
	int year;
	

	while (!feof(f)) {	//dok ne dode do kraja
		fscanf(f, "%s %s %d\n", fname, lname, &year);	//cita iz filea
		err=addLast(fname, lname, year, p);	//upisuje na kraj liste

		if(err==MALLOC_ERROR) return MALLOC_ERROR;	//ispisuje error ako postoji
	}

	fclose(f);
	return 0;
}
