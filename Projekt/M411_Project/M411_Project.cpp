// M411_Project.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "String.h"
#include "time.h"

//Struct für Daten
struct Daten {
	char Vorname[5];
	char Nachname[5];
	int Jahrgang;
	int Nummer;
};
typedef struct Daten struData;

//Struct für Grundgerüst
struct Person {
	struData* pData;
	struct Person* pNext;
	struct Person* pPrev;
};
typedef struct Person struPer;

void Output(struPer* pStart) {
	//Gibt Liste aus
	if (pStart != NULL) {
		printf("Liste:\n\n");
		for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
			printf("%i, ", pOut->pData->Nummer);
			printf("%s, ", pOut->pData->Vorname);
			printf("%s, ", pOut->pData->Nachname);
			printf("%i\n", pOut->pData->Jahrgang);
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
		pNew->pData = (struData *)malloc(sizeof(struData));
		pNew->pData->Jahrgang = randjahr();
		pNew->pData->Nachname[0] = randbuchstabe();
		pNew->pData->Nachname[1] = '\0';
		pNew->pData->Vorname[0] = randbuchstabe();
		pNew->pData->Vorname[1] = '\0';
		pNew->pData->Nummer = iPer + 1;

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

//Mit Nummer Löschen
void delElmnummer(int nummer, struPer* pStart) {
	for (struPer* pDel = pStart->pNext; nummer != (pDel->pData->Nummer - 1); pDel = pDel->pNext) {
		struPer* tmp = pDel->pNext;
		pDel->pNext = pDel->pNext->pNext;
		free(tmp);
		printf("Element erfolgreich gelöscht!\n\n");
	}
}

//Mit Name und Vorname Löschen
void delElmchar(struPer* pStart, char vorname[5], char nachname[5]) {
	struPer* pCurrent = pStart;
	while (pCurrent != NULL) {
		struPer* pDel = pCurrent->pNext;
		if (strcmp(pDel->pData->Vorname, vorname) == 0 && strcmp(pDel->pData->Nachname, nachname) == 0){
			struPer* tmp = pDel->pNext;
			pDel->pNext = pDel->pNext->pNext;
			free(tmp);
		}
	}
		printf("Element erfolgreich gelöscht!\n\n");	
}

//Sort: Schreibt die Pointer um
void SortNew(struPer* pStart) {
	bool issortingnew = true;
	while (issortingnew) {
		issortingnew = false;
		for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
			if (strcmp(pSort->pData->Nachname, pSort->pNext->pData->Nachname) > 0) {
				pSort->pNext->pPrev = pSort->pPrev;
				pSort->pNext = pSort->pNext->pNext;
				pSort->pNext->pNext->pPrev = pSort->pNext->pPrev;
				pSort->pNext->pNext = pSort;
				issortingnew = true;
			}
			if (strcmp(pSort->pData->Nachname, pSort->pNext->pData->Nachname) == 0 && strcmp(pSort->pData->Vorname, pSort->pNext->pData->Vorname) > 0) {
				pSort->pNext->pPrev = pSort->pPrev;
				pSort->pNext = pSort->pNext->pNext;
				pSort->pNext->pNext->pPrev = pSort->pNext->pPrev;
				pSort->pNext->pNext = pSort;
				issortingnew = true;
			}
		}
	}
}

//Sort: Kopiert die Werte und Sortiert Namen und Vornamen nach Alphabet
void Sort(struPer* pStart) {
	bool issorting = true;
	while (issorting) {
		issorting = false;
		for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
			if (pSort->pData->Nachname != NULL) {
				if (strcmp(pSort->pData->Nachname, pSort->pNext->pData->Nachname) > 0) {
					char tmpname[5];
					strcpy_s(tmpname, pSort->pData->Nachname);
					strcpy_s(pSort->pData->Nachname, pSort->pNext->pData->Nachname);
					strcpy_s(pSort->pNext->pData->Nachname, tmpname);
					char tmpvorname[5];
					strcpy_s(tmpvorname, pSort->pData->Vorname);
					strcpy_s(pSort->pData->Vorname, pSort->pNext->pData->Vorname);
					strcpy_s(pSort->pNext->pData->Vorname, tmpvorname);
					int tmpjahr;
					tmpjahr = pSort->pData->Jahrgang;
					pSort->pData->Jahrgang = pSort->pNext->pData->Jahrgang;
					pSort->pNext->pData->Jahrgang = tmpjahr;
					issorting = true;
				}
			}
			if (pSort->pData->Vorname != NULL) {
				if (strcmp(pSort->pData->Nachname, pSort->pNext->pData->Nachname) == 0 && strcmp(pSort->pData->Vorname, pSort->pNext->pData->Vorname) > 0) {
					char tmpvorname[5];
					strcpy_s(tmpvorname, pSort->pData->Vorname);
					strcpy_s(pSort->pData->Vorname, pSort->pNext->pData->Vorname);
					strcpy_s(pSort->pNext->pData->Vorname, tmpvorname);
					char tmpname[5];
					strcpy_s(tmpname, pSort->pData->Nachname);
					strcpy_s(pSort->pData->Nachname, pSort->pNext->pData->Nachname);
					strcpy_s(pSort->pNext->pData->Nachname, tmpname);
					int tmpjahr;
					tmpjahr = pSort->pData->Jahrgang;
					pSort->pData->Jahrgang = pSort->pNext->pData->Jahrgang;
					pSort->pNext->pData->Jahrgang = tmpjahr;
					issorting = true;
				}
			}
		}
	}
}

//Sort: Kopiert die Werte und sortiert nach dem Jahrgang (jüngste zuerst)
void SortJahrgang(struPer* pStart) {
	bool issorting = true;
	while (issorting) {
		issorting = false;
		for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
			if (pSort->pData->Jahrgang != NULL) {
				if (pSort->pData->Jahrgang < pSort->pNext->pData->Jahrgang) {
					char tmpname[5];
					strcpy_s(tmpname, pSort->pData->Nachname);
					strcpy_s(pSort->pData->Nachname, pSort->pNext->pData->Nachname);
					strcpy_s(pSort->pNext->pData->Nachname, tmpname);
					char tmpvorname[5];
					strcpy_s(tmpvorname, pSort->pData->Vorname);
					strcpy_s(pSort->pData->Vorname, pSort->pNext->pData->Vorname);
					strcpy_s(pSort->pNext->pData->Vorname, tmpvorname);
					int tmpjahr;
					tmpjahr = pSort->pData->Jahrgang;
					pSort->pData->Jahrgang = pSort->pNext->pData->Jahrgang;
					pSort->pNext->pData->Jahrgang = tmpjahr;
					issorting = true;
				}
			}
		}
	}
}

void QuickSort() {

}

//Element nach Namen und Vorname suchen
void elementsuchen(struPer* pStart, char vorname[5], char nachname[5]) {
	struPer* pSearch = NULL;
	while (pStart != NULL) {
		bool vergleich = strcmp(pStart->pData->Nachname, nachname) == 0 && strcmp(pStart->pData->Vorname, vorname) == 0;
		if (vergleich) {
			printf("Das gesuchte Element ist vorhanden!");
		}
		else if (pStart == NULL) {
			printf("Element nicht gefunden\n");
		}
	}
}

//Main mit allen Optionen
int main()
{
	int anz = 0;
	char answer = 0;
	int nummer = 0;
	char vorname[5];
	char nachname[5];

	printf("Bitte Anzahl Elemente eingeben: ");
	scanf_s("%i", &anz);
	struPer* pStart = Create(anz);
	Output(pStart);

	while (true) {
		if (pStart != NULL) {
			printf("Moechten sie die Liste nach Alphabet sortieren? [s]\n");
			printf("Moechten sie die Liste nach dem dazugehörigen Jahrgang Sortieren? [j]\n");
			printf("Wollen sie ein Element löschen anhand der Nummer? [l]\n");
			printf("Wollen sie ein Element löschen anhand des Vor- und Nachnamens? [c]\n");			
			printf("Moechten sie die gesammte Liste löschen? [g]\n");
			printf("Moechten sie die Liste noch einmal ausgeben? [a]\n");
			printf("Moechten sie die Konsole Leeren? [k]\n");
			printf("Moechten sie die Applikatoin beenden? [x]\n");
			printf("Moechten sie nach einem Bestimmten Element suchen? [f]\n");
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
			case 'k':
				system("@cls||clear");
				break;
			case 'x':
				return 0;
				break;
			case 'f':
				printf("Bitte Vorname eingeben: ");
				scanf_s("%c", &vorname);
				printf("Bitte Nachname eingeben: ");
				scanf_s("%c", &nachname);
				elementsuchen(pStart, vorname, nachname);
				break;
			case 'j':
				SortJahrgang(pStart);
				break;
			default:
				printf("Die Eingabe ist nicht Gueltig!\n\n");
				break; 
			}
			//Buffer Leeren
			fseek(stdin, 0, SEEK_END);
		}
	}
}

