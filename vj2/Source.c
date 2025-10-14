#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

 struct Osoba {	//struktura osoba
	char* f_name;
	char* l_name;
	int year;

	struct Osoba* next;	//pointer na iducu osobu u listi
};

 typedef struct Osoba osoba;

int addFirst(char*, char*, int, osoba*);	//dodaje novu osobu na start
int printList(osoba*);	//ispisuje sve clanove
int addLast(char*, char*, int, osoba*);	//dodaje novu osobu na kraj

int main() {
	osoba* head = (osoba*)malloc(sizeof(osoba));	//head element liste
	head->next = NULL;

	addFirst("jakov", "jozic", 2005, head);
	addFirst("laura", "matas", 2002, head);
	addLast("idk", "lol", 2010, head);
	printList(head->next);

	free(head);
	return 0;
}

int addFirst(char* fname, char* lname, int year, osoba* anchor) {
	osoba* new = (osoba*)malloc(sizeof(osoba));	//alociranje nove osobe
	new->f_name = fname;
	new->l_name = lname;
	new->year = year;
	new->next = anchor->next;

	anchor->next = new;	//postavljanje na pocetak

	return 0;
}

int printList(osoba* anchor) {
	while (anchor) {
		printf("%s %s %d\n", anchor->f_name, anchor->l_name, anchor->year);
		anchor = anchor->next;
	}
	return 0;
}

int addLast(char* fname, char* lname, int year, osoba* anchor) {
	while (anchor->next) {	//pronalazi zadnji clan
		anchor = anchor->next;
	}

	addFirst(fname, lname, year, anchor); //anchor je sada zadnji clan pa dodaje na kraj

	return 0;
}