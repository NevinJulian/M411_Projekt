// M411_Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "String.h"
#include "stdafx.h"
#include "time.h"

struct Person {
	char Vorname[40];
	char Nachname[40];
	int Jahrgang;
	int Nummer;
	struct Person* pNext;
};

typedef struct Person struPer;

void Output(struPer* pStart) {
	//Gibt Liste aus
	printf("Liste:\n\n");
	for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
		printf("%c\n", pOut->Vorname);
		printf("%c\n", pOut->Nachname);
		printf("%i\n", pOut->Jahrgang);
	}
}

struPer* Create(int Anzahl) {
	//Erstellt eine Liste von definierter Anzahl Elemente
	struPer* pStart = NULL;
	struPer* pLast = NULL;

	for (int iPer = 0; iPer < Anzahl; iPer++) {
		struPer* pNew = (struPer*)malloc(sizeof(struPer));
		pNew->Nummer = iPer + 1;
		pNew->pNext = NULL;
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
	}
	return pStart;
}

int randjahr() {

}

void delPer() {

}

int main()
{
	int anz = 0;
	char answer = 'a';
	//Zufallszahl generieren
	srand((unsigned) time(NULL));

	printf("Bitt Anzahl Elemente eingeben: ");
	scanf_s("%i", anz);
	struPer* pStart = Create(anz);
	Output(pStart);
	system("pause");
	printf("Wollen sie eine Person löschen? [Ja => j] [Nein =>n]");
	scanf_s("%c", answer);
	if (answer == 'j') {
		printf("Welche Person möchten sie löschen?");
		scanf_s("");
	}
}

