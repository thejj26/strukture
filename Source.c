#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SCORE 20
//-1 => file not found
//1 => malloc failed

typedef struct {
	char f_name[20];
	char l_name[20];
	int score;
} student;

int countStudents(char*);	//broji linije tj studente
int loadStudents(char*, student*);
float calcScore(int);	//racuna relativne bodove
int printStudentInfo(student*);	//ispisuje podatke za odabranog studenta

void main() {
	int n=0;//broj studenata
	int i=0;	//iterator

	n = countStudents("data.txt");
	if (n) return n;

	printf("Ima %d studenata\n\n", n);

	student* students = (student*)malloc(n * sizeof(student));	//alocira se niz studenata pomocu pokazivaca
	if (students == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	loadStudents("data.txt", n, students);
	if (n) return n;

	//ispis studenata
	for (i = 0; i < n; i++) {	//prolazi kroz sve studente
		printStudentInfo(students+i);	//ispisuje podatke
	}
}

int countStudents(char* path) {
	int n = 0;
	FILE* f =fopen(path, "r");
	if (f == NULL) {
		printf("FILE NOT FOUND\n");
		return -1;
	}

	while (!feof(f)) {	//vrti se dok ne dode do kraja filea
		fscanf(f,"%*c\n");	//uzima liniju bilo koji znakova koja zavrsava s \n
		n++;
	}

	fclose(f);
	return n;
}

int loadStudents(char* path, student* students) {
	FILE* f = fopen(path, "r");
	int i=0;	//iterator

	if (f == NULL) {
		printf("FILE NOT FOUND\n");
		return -1;
	}

	while (!feof(f)) {
		fscanf(f, "%*c %*c %d\n", students[i].f_name, students[i].l_name, students[i].score);	//ucitaje podatke u odabranu instancu strukture
		i++;	//iterator se inkrementira, ide se na iduceg studenta
	}

	fclose(f);
	return 0;
}

float calcScore(int score) {
	return(float)score / MAX_SCORE * 100;
}

int printStudentInfo(student* s) {
	printf("%*c %*c %.2f\n", s->f_name, s->l_name, calcScore(s->score));	//ispisuje podatke pomocu printf
	return 0;
}