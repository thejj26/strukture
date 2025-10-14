#define _CRT_SECURE_NO_WARNINGS
#define  EMPTY_LIST -1

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
	person* head = (person*)malloc(sizeof(person));	//head element liste
	head->next = NULL;

	//dodavanje novih osoba
	addFirst("jakov", "jozic", 2006, head);	
	addFirst("laura", "matas", 2002, head);
	addLast("idk", "lol", 2010, head);

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
	delete(lastName, head);
	printf("Ta je osoba sada izbrisana.\n\n");
	printList(head->next);

	printf("\n");
	free(head);
	return 0;
}

int addFirst(char* fname, char* lname, int year, person* anchor) {
	person* new = (person*)malloc(sizeof(person));	//alociranje nove osobe
	new->f_name = fname;
	new->l_name = lname;
	new->year = year;
	new->next = anchor->next;

	anchor->next = new;	//postavljanje na pocetak

	return 0;
}

int printList(person* anchor) {
	while (anchor) {	//sve dok je valjani clan(adresa nije null)
		printf("%s %s %d\n", anchor->f_name, anchor->l_name, anchor->year);
		anchor = anchor->next;	//prelazak na iduci clan
	}

	return 0;
}

int addLast(char* fname, char* lname, int year, person* anchor) {
	while (anchor->next) {	//pronalazi zadnji clan
		anchor = anchor->next;
	}

	addFirst(fname, lname, year, anchor); //anchor je sada zadnji clan pa dodaje na kraj

	return 0;
}

person* findByLastName(char* lname, person* anchor){
	while(anchor){
		if(!strcmp(anchor->l_name, lname)) break;	//usporeduje stringove, ako su jednaki prekida petlju
		anchor=anchor->next;
	}

	return anchor;
}

int delete(char* lname, person* anchor){
	if(!anchor->next) return EMPTY_LIST;	//ukoliko nema elemenata

	while(anchor->next){	//trazi prezime u iducem elementu
		if(!strcmp(anchor->next->l_name, lname)) break;	//usporeduje stringove, ako su jednaki prekida petlju
		anchor=anchor->next;
	}

	person* temp=anchor->next;
	anchor->next=temp->next;
	free(temp);

	return 0;
}