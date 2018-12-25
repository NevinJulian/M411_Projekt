// M411_Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "String.h"
#include "time.h"

struct Person {
	char Vorname[5];
	char Nachname[5];
	int Jahrgang;
	int Nummer;
	struct Person* pNext;
	struct Person* pPrev;
};

typedef struct Person struPer;

void Output(struPer* pStart) {
	//Gibt Liste aus
	if (pStart != NULL) {
		printf("Liste:\n\n");
		for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
			printf("%i, ", pOut->Nummer);
			printf("%s, ", pOut->Vorname);
			printf("%s, ", pOut->Nachname); 
			printf("%i\n", pOut->Jahrgang);
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
		pNew->pPrev = pLast;

		if (pStart == NULL) {
			pStart = pNew;
		}
		if (pLast != NULL) {
			pLast->pNext = pNew;
		}
		pLast = pNew;
	}
	return pStart;
}

void delElmnummer(int nummer, struPer* pStart) {
	for (struPer* pDel = pStart->pNext; nummer != (pDel->Nummer - 1); pDel = pDel->pNext) {
		struPer* tmp = pDel->pNext;
		pDel->pNext = pDel->pNext->pNext;
		free(tmp);
		printf("Element erfolgreich gelöscht!\n\n");
	}
}

void delElmchar(struPer* pStart, char vorname, char nachname) {
	struPer* pCurrent = pStart;
	while (pCurrent != NULL) {
		struPer* pDel = pCurrent->pNext;
		if (pDel->Vorname[0] == vorname && pDel->Nachname[0] == nachname) {
			struPer* tmp = pDel->pNext;
			pDel->pNext = pDel->pNext->pNext;
			free(tmp);
		}
	}
		printf("Element erfolgreich gelöscht!\n\n");	
}

//Neuer Sort
void Sort(struPer* pStart) {
	for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
		if (strcmp(pSort->Nachname, pSort->pNext->Nachname) > 0) {
			pSort->pNext->pPrev = pSort->pPrev;
			pSort->pNext = pSort->pNext->pNext;
			pSort->pNext->pNext->pPrev = pSort->pNext->pPrev;
			pSort->pNext->pNext = pSort;
		}
		if (strcmp(pSort->Nachname, pSort->pNext->Nachname) == 0 && strcmp(pSort->Vorname, pSort->pNext->Vorname) > 0) {
			pSort->pNext->pPrev = pSort->pPrev;
			pSort->pNext = pSort->pNext->pNext;
			pSort->pNext->pNext->pPrev = pSort->pNext->pPrev;
			pSort->pNext->pNext = pSort;
		}
	}
}


//Alter Sort
void SortAlt(struPer* pStart) {
	for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
		if (pSort->Nachname != NULL) {
			if (strcmp(pSort->Nachname, pSort->pNext->Nachname) > 0) {
				char tmpname[5];
				strcpy_s(tmpname, pSort->Nachname);
				strcpy_s(pSort->Nachname, pSort->pNext->Nachname);
				strcpy_s(pSort->pNext->Nachname, tmpname);
			}
		}
		if (pSort->Vorname != NULL) {
			if (strcmp(pSort->Nachname, pSort->pNext->Nachname) == 0) {
				char tmpvorname[5];
				strcpy_s(tmpvorname, pSort->Vorname);
				strcpy_s(pSort->Vorname, pSort->pNext->Vorname);
				strcpy_s(pSort->pNext->Vorname, tmpvorname);
			}
		}
	}
}

int main()
{
	int anz = 0;
	char answer = 0;
	int nummer = 0;
	char vorname;
	char nachname;

	printf("Bitte Anzahl Elemente eingeben: ");
	scanf_s("%i", &anz);
	struPer* pStart = Create(anz);
	Output(pStart);

	while (true) {
		if (pStart != NULL) {
			printf("Moechten sie die Liste nach Alphabet sortieren? [s]\n");
			printf("Wollen sie ein Element löschen anhand der nummer? [l]\n");
			printf("Wollen sie ein Element löschen anhand des Vor- und Nachnamens? [c]\n");			
			printf("Moechten sie die gesammte Liste löschen? [g]\n");
			printf("Moechten sie die Liste noch einmal ausgeben? [a]\n");
			scanf_s("%c", &answer);

			switch (answer) {
			case 's':
				Sort(pStart);
				break;
			case 'l':
				printf("Bitte die Nummer des Elementes eingeben: ");
				scanf_s("%i", &nummer);
				delElmnummer(nummer, pStart);
				break;
			case 'c':
				printf("Bitte Vorname eingeben: ");
				scanf_s("%c", &vorname);
				printf("Bitte Nachname eingeben: ");
				scanf_s("%c", &nachname);
				delElmchar(pStart, vorname, nachname);
				break;
			case 'g':
				pStart = NULL;
				break;
			case 'a':
				Output(pStart);
				break;
			default:
				printf("Die Eingabe ist nicht Gueltig!\n");
				break;
			}
		}
	}
}

