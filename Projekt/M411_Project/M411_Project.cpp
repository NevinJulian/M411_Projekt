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
	if (pStart != NULL) {
		printf("Liste:\n\n");
		for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
			printf("%i\n", pOut->Nummer);
			printf("%s\n", pOut->Vorname);
			printf("%s\n", pOut->Nachname);
			printf("%i\n\n", pOut->Jahrgang);
		}
	}
	else {
		printf("Es sind keine Elemente vorhanden!");
	}
}

int randjahr() {
	int zahl = 1900 + rand() % 118;
	return zahl;
}

char randbuchstabe() {
	return rand() % 26 + 'A';
}

struPer* Create(int Anzahl) {
	//Erstellt eine Liste von definierter Anzahl Elemente
	srand((unsigned)time(NULL));
	struPer* pStart = NULL;
	struPer* pLast = NULL;

	for (int iPer = 0; iPer < Anzahl; iPer++) {
		struPer* pNew = (struPer*)malloc(sizeof(struPer));
		pNew->Jahrgang = randjahr();
		pNew->Nachname[0] = randbuchstabe();
		pNew->Nachname[1] = '\0';
		pNew->Vorname[0] = randbuchstabe();
		pNew->Vorname[1] = '\0';
		pNew->Nummer = iPer + 1;
		pNew->pNext = NULL;
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
	}
	return pStart;
}

void delElm(int nummer, struPer* pStart) {
	for (struPer* pDel = pStart->pNext; nummer != (pDel->Nummer - 1); pDel = pDel->pNext) {
		struPer* tmp = pDel->pNext;
		pDel->pNext = pDel->pNext->pNext;
		free(tmp);
		printf("Element erfolgreich gelöscht!\n\n");
	}
}

struPer* Sort() {

}

int main()
{
	int anz = 0;
	char answer = 0;
	int nummer = 0;

	printf("Bitt Anzahl Elemente eingeben: ");
	scanf_s("%i", &anz);
	struPer* pStart = Create(anz);
	Output(pStart);
	while(true){
		printf("Moechten sie die Liste nach Alphabet sortieren? [s]\n");
		printf("Wollen sie ein Element löschen? [l]\n");
		printf("Moechten sie die gesammte Liste löschen? [g]\n");
		printf("Moechten sie die Liste noch einmal ausgeben? [a]\n");
		scanf_s("%c", &answer);

		switch (answer) {
		case 's':
			//Liste Sortieren
			break;
		case 'l':
			printf("Bitte die Nummer des Elementes eingeben: ");
			scanf_s("%i", &nummer);
			delElm(nummer, pStart);
			break;
		case 'g':
			//Gesammte Liste Leeren
			break;
		case 'a':
			Output(pStart);
			break;
		default:
			printf("Die Eingabe ist nicht Gueltig!");
			break;
		}

		system("pause");
	}
}

