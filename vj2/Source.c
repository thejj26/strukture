#define _CRT_SECURE_NO_WARNINGS
#define  EMPTY_LIST -1
#define MALLOC_ERROR -2

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
person* findByLastName(char*, person*);	//pronalazi osobu po prezimenu
int delete(char*, person*);	//brise osobu po prezimenu

int main() {
	int err_handler=0;	//za lakse spremanje return vrijednosti

	person* head = (person*)malloc(sizeof(person));	//head element liste
	head->next = NULL;

	//dodavanje novih osoba
	err_handler=addFirst("jakov", "jozic", 2006, head);	
	if(err_handler) return err_handler;
	err_handler=addFirst("laura", "matas", 2002, head);
	if(err_handler) return err_handler;
	err_handler=addLast("idk", "lol", 2010, head);
	if(err_handler) return err_handler;

	printf("\n");
	printList(head->next);	//ispis svih osoba

	//unos prezimena
	char lastName[10];
	printf("\nUnesite trazeno prezime: ");
	scanf("%s",lastName);
	getc(stdin);

	//pretraga po prezimenu
	person* temp=findByLastName(lastName, head->next);
	if(!temp){
		printf("Nema osobe s tim prezimenom\n");
	}else{
		printf("Osoba s tim prezimenom je %s %s, rodena %d. godine\n",temp->f_name, temp->l_name, temp->year);
	}

	//brisane po prezimenu
	err_handler=delete(lastName, head);
	if(err_handler) return err_handler;
	printf("Ta je osoba sada izbrisana.\n\n");
	printList(head->next);

	printf("\n");
	free(head);
	return 0;
}

int addFirst(char* fname, char* lname, int year, person* p) {
	person* new = (person*)malloc(sizeof(person));	//alociranje nove osobe
	if(!new) return MALLOC_ERROR;

	new->f_name = fname;
	new->l_name = lname;
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

	addFirst(fname, lname, year, p); //p je sada zadnji clan pa dodaje na kraj

	return 0;
}

person* findByLastName(char* lname, person* p){
	while(p){
		if(!strcmp(p->l_name, lname)) break;	//usporeduje stringove, ako su jednaki prekida petlju
		p=p->next;
	}

	return p;
}

int delete(char* lname, person* p){
	if(!p->next) return EMPTY_LIST;	//ukoliko nema elemenata

	while(p->next){	//trazi prezime u iducem elementu
		if(!strcmp(p->next->l_name, lname)) break;	//usporeduje stringove, ako su jednaki prekida petlju
		p=p->next;
	}

	person* temp=p->next;
	p->next=temp->next;
	free(temp);

	return 0;
}