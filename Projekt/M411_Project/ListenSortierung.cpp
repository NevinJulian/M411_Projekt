// M411_Project.cpp : Defines the entry point for the console application.
//Alle Funktionen wurden in Partnerarbeit geschrieben, dei einzige Ausnahme ist die listinlist Funktion
//Diese wurde von Nevin Helfenstein erstellt.
//ALLES andere wurde in Zusammenarbeit erledigt
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
	int Listevorhanden;
};
typedef struct Daten struData;

//Struct für Grundgerüst
struct Person {
	struData* pData;
	struct Person* pNext;
	struct Person* pPrev;
	struct Person* pList;
};
typedef struct Person struPer;

void Output(struPer* pStart, int anz) {
	//Gibt Liste aus
	if (pStart != NULL) {
		int i = 1;
		printf("\n\nListe:\n\n");

		if (anz == 0) {
			for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
				printf("%i, ", pOut->pData->Nummer);
				printf("%s, ", pOut->pData->Nachname);
				printf("%s, ", pOut->pData->Vorname);
				printf("%i\n", pOut->pData->Jahrgang);
			}
		}
		else{
			for (struPer* pOut = pStart; i <= anz; pOut = pOut->pNext) {
				printf("%i, ", pOut->pData->Nummer);
				printf("%s, ", pOut->pData->Nachname);
				printf("%s, ", pOut->pData->Vorname);
				printf("%i\n", pOut->pData->Jahrgang);
			}
			}
		}
	else {
		printf("Es sind keine Elemente vorhanden!");
	}
}

//Generiert ein Random Jahr
int randjahr() {
	int zahl = 1900 + rand() % 118;
	return zahl;
}

//Generiert ein Random Buchstabe
char randbuchstabe() {
	return rand() % 26 + 'A';
}

struPer* Create(int Anzahl) {
	//Erstellt eine Liste von definierter Anzahl Elemente
	srand((unsigned)time(NULL));
	struPer* pStart = NULL;
	struPer* pPrev = NULL;
	struPer* pList = NULL;

	for (int iPer = 0; iPer < Anzahl; iPer++) {
		struPer* pNew = (struPer*)malloc(sizeof(struPer));
		pNew->pData = (struData *)malloc(sizeof(struData));
		pNew->pList = (struPer *)malloc(sizeof(struPer));
		//pNew->pList->pData = (struData *)malloc(sizeof(struData));
		pNew->pData->Listevorhanden = 0;
		pNew->pData->Jahrgang = randjahr();
		pNew->pData->Nachname[0] = randbuchstabe();
		pNew->pData->Nachname[1] = '\0';
		pNew->pData->Vorname[0] = randbuchstabe();
		pNew->pData->Vorname[1] = '\0';
		pNew->pData->Nummer = iPer + 1;

		pNew->pNext = NULL;
		pNew->pPrev = pPrev;

		if (pStart == NULL) {
			pStart = pNew;
		}
		if (pPrev != NULL) {
			pPrev->pNext = pNew;
		}
		pPrev = pNew;
	}
	return pStart;
}

//Mit Nummer Löschen (Löscht ein Element mit einer mitgegebenen Nummer)
struPer* delElmnummer(int nummer, struPer* pStart) {
		struPer* pDel = pStart; 
		while (nummer != (pDel->pData->Nummer)) {
			pDel = pDel->pNext;
		}
		if (nummer == (pDel->pData->Nummer)) {
			struPer* tmp = pDel;
			if (pDel->pPrev != NULL) {
				pDel->pPrev->pNext = pDel->pNext;
				free(tmp);
			}
			else if (pDel->pPrev == NULL) {
				pStart = pDel->pNext;
			}
			printf("Element erfolgreich gelöscht!\n\n");
		}
		return pStart;
}

//Mit Name und Vorname Löschen (Löscht ein Element mit mitgegebenem Namen)
struPer* delElmchar(struPer* pStart, char vorname[5], char nachname[5]) {
	struPer* pCurrent = pStart;

	while (pCurrent != NULL) {
		struPer* pNext = pCurrent->pNext;

		if (strcmp(pCurrent->pData->Vorname, vorname) == 0 && strcmp(pCurrent->pData->Nachname, nachname) == 0) {
			if (pCurrent->pPrev == NULL) {
				pCurrent->pNext->pPrev = NULL;
				pStart = pCurrent->pNext;
				free(pCurrent);
			}
			else {
				struPer* tmp = pCurrent->pNext;
				pCurrent->pNext = pCurrent->pNext->pNext;
				free(tmp);
			}
		}
		pCurrent = pNext;
	}
	printf("Element erfolgreich gel\224scht!\n\n");
	return pStart;
}

//Sort: Schreibt die Daten um (Keine Daten werden wirklich kopiert)
//Dieser Sort ist um einiges Schneller als der Sort wo die Daten kopiert werden müssen
void SortNew(struPer* pStart) {
	struData* pTmp = NULL;
	clock_t begin = clock();
	for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
		for (struPer * pSort2 = pSort->pNext; pSort2 != NULL; pSort2 = pSort2->pNext) {
			if (pSort->pData->Nachname[0] > pSort2->pData->Nachname[0]) {
				pTmp = pSort->pData;
				pSort->pData = pSort2->pData;
				pSort2->pData = pTmp;
			}
			if (pSort->pData->Nachname[0] == pSort2->pData->Nachname[0]) {
				if (pSort->pData->Vorname[0] > pSort2->pData->Vorname[0]) {
					pTmp = pSort->pData;
					pSort->pData = pSort2->pData;
					pSort2->pData = pTmp;
				}
			}
		}
	}
	clock_t end = clock();
	printf("Sort: %i ms", (end - begin));
}

//Sort: Kopiert die Werte und Sortiert Namen und Vornamen nach Alphabet
void Sort(struPer* pStart) {
	clock_t begin = clock();
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
	clock_t end = clock();
	printf("Sort: %i ms", (end - begin));
}

//Sort: Kopiert die Werte und sortiert nach dem Jahrgang (jüngste zuerst)
void SortJahrgangNew(struPer* pStart) {
	struData* pTmp = NULL;
	clock_t begin = clock();
	for (struPer* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext) {
		for (struPer * pSort2 = pSort->pNext; pSort2 != NULL; pSort2 = pSort2->pNext) {
			if(pSort->pData->Jahrgang < pSort2->pData->Jahrgang) {
				pTmp = pSort->pData;
				pSort->pData = pSort2->pData;
				pSort2->pData = pTmp;
			}
		}
	}
	clock_t end = clock();
	printf("Sort: %i ms", (end - begin));
}

//Sort: Kopiert die Werte und sortiert nach dem Jahrgang (jüngste zuerst)
void SortJahrgang(struPer* pStart) {
	clock_t begin = clock();
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
	clock_t end = clock();
	printf("Sort: %i ms", (end - begin));
}


//eigene Idee: Liste Innerhalb der Liste
void listinlist(struPer* pStart, int current) {
	//Current ist das Node aufdem die Liste aufgebaut wird
	struPer* pCurrent = pStart;
	int Anzahl;
	printf("Bitte Anzahl der Elemente der Liste eingeben: ");
	scanf_s("%i", &Anzahl);
	struPer* list = Create(Anzahl);
	
	while (pCurrent != NULL && pCurrent->pData->Nummer <= current) {
		if (pCurrent->pData->Nummer == current) {
			pCurrent->pList = list;
			pCurrent->pData->Listevorhanden = 1;
		}
		pCurrent = pCurrent->pNext;
	}
}

//Output von mehrdimensinalen Listen
void OutputDimensional(struPer* pStart) {
	//Gibt mehrdimensionale Liste aus
	if (pStart != NULL) {
		for (struPer* pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
			if (pOut->pData->Listevorhanden == 0) {
				printf("%i, ", pOut->pData->Nummer);
				printf("%s, ", pOut->pData->Vorname);
				printf("%s, ", pOut->pData->Nachname);
				printf("%i\n", pOut->pData->Jahrgang);
			}
			else if(pOut->pData->Listevorhanden == 1){
				printf("%i, ", pOut->pData->Nummer);
				printf("%s, ", pOut->pData->Vorname);
				printf("%s, ", pOut->pData->Nachname);
				printf("%i\n", pOut->pData->Jahrgang);
				for (struPer* pOut2 = pOut->pList; pOut2 != NULL; pOut2 = pOut2->pNext) {
					printf("\t%i, ", pOut2->pData->Nummer);
					printf("%s, ", pOut2->pData->Vorname);
					printf("%s, ", pOut2->pData->Nachname);
					printf("%i\n", pOut2->pData->Jahrgang);
				}
			}
		}
	}
	else {
		printf("Es sind keine Elemente vorhanden!");
	}
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

//Findet den Index eines Elementes (Name und Voname sind mitgegen)
int indexfinden(struPer* pStart, char vorname[5], char nachname[5]) {
	struPer* pSearch = NULL;
	int index = 1;
	while (pStart != NULL) {
		bool vergleich = strcmp(pStart->pData->Nachname, nachname) == 0 && strcmp(pStart->pData->Vorname, vorname) == 0;
		if (vergleich) {
			return index;
		}
		else if (pStart == NULL) {
			printf("Element nicht gefunden\n");
			return 0;
		}
		index++;
	}
	return 0;
}

//Wird am Anfang und beim Neustart des Programmes ausgeführt
struPer* Start() {
	int anz = 0;
	printf("*************************************M411 Projekt*************************************");
	printf("\n\t\t\tVerkettete Liste von Nevin und Lino");
	printf("\n**************************************************************************************");
	printf("\n\nBitte Anzahl Elemente eingeben: ");
	scanf_s("%i", &anz);
	struPer* pStart = Create(anz);
	Output(pStart, 0);
	return pStart;
}

//Main mit allen Optionen
int main()
{
	int anz = 0;
	char answer;
	int nummer = 0;
	char vorname[5];
	char nachname[5];
	int anzelm = 0;
	char auswahl;
	int index;
	char begin;
	int unterlistenr;

	struPer* pStart = Start();

	while (true) {
		if (pStart != NULL) {

			//Buffer Leeren
			fseek(stdin, 0, SEEK_END);
			printf("\n\n---------------Ereignisse--------------- \n\n");
			printf("Was m\224chten sie machen?\n");
			printf("|Liste nach Alphabet sortieren? [s]\n");
			printf("|Liste nach dem Jahrgang Sortieren? [j]\n\n");
			printf("|Element l\244schen anhand der Nummer? [l]\n");
			printf("|Element l\224schen anhand des Vor- und Nachnamens? [c]\n");			
			printf("|Die gesammte Liste l\224schen? [g]\n\n");
			printf("|Die Liste entfernen? [e]");
			printf("|Die Liste noch einmal ausgeben? [a]\n");
			printf("|Die Konsole Leeren? [k]\n");
			printf("|Die Applikatoin beenden? [x]\n");
			printf("|Nach einem Bestimmten Element suchen? [f]\n\n");
			printf("|Eine Liste Innerhalb dieser Liste aufbauen? [n]\n");
			printf("|Die Liste mit Unterlisten ausgeben? [u]\n");
			scanf_s("%c", &answer, 1);

			//Buffer Leeren
			fseek(stdin, 0, SEEK_END);

			//Main mit switch case
			switch (answer) {
			case 's':
			case 'S':
				SortNew(pStart);
				break;
			case 'l':
			case 'L':
				printf("Bitte die Nummer des Elementes eingeben: ");
				scanf_s("%i", &nummer);
				pStart = delElmnummer(nummer, pStart);

				break;
			case 'c':
			case 'C':
				printf("Bitte Vorname eingeben: ");
				gets_s(vorname);
				printf("Bitte Nachname eingeben: ");
				gets_s(nachname);
				pStart = delElmchar(pStart, vorname, nachname);
				
				break;
			case 'g':
			case 'G':
				pStart = NULL;
				printf("Sie haben die gesammte Liste gel\224scht!\n");
				printf("Wollen sie von Vorne beginnen? [j/n]");
				scanf_s("%c", &begin);
				if (begin == 'j') {
					system("@cls||clear");
					main();
				}
				else if (begin == 'n') {
					return 0;
				}
				break;
			case 'a':
			case 'A':
				printf("Wie viele Elemente wollen sie ausgeben? [0 = Alle]");
				scanf_s("%i", &anzelm);
				Output(pStart, anzelm);
				break;
			case 'k':
			case 'K':
				system("@cls||clear");
				break;
			case 'x':
			case 'X':
				return 0;
				break;
			case 'f':
			case 'F':
				printf("Bitte Vorname eingeben: ");
				gets_s(vorname);
				printf("Bitte Nachname eingeben: ");
				gets_s(nachname);
				elementsuchen(pStart, vorname, nachname);
				break;
			case 'j':
			case 'J':
				SortJahrgangNew(pStart);
				break;
			case 'n':
			case 'N':
				printf("M\224chten sie das Element per Name[n] oder per Nummer[z] suchen? (Nummer ist genauer)");
				scanf_s("%c", &auswahl, 1);
				if (auswahl == 'n') {
					printf("Bitte Vorname eingeben: \n");
					gets_s(vorname);
					printf("Bitte Nachname eingeben: \n");
					gets_s(nachname);
					index = indexfinden(pStart, vorname, nachname);
					listinlist(pStart, index);
				}
				else if (auswahl == 'z') {
					printf("Bitte Nummer eingeben: \n");
					scanf_s("%i", &index);
					if (index > anz) {
						printf("Dieses Element existiert nicht!\n");
						printf("Bitte Gültige nummer eingeben: ");
						scanf_s("%i", &index);
					}
					listinlist(pStart, index);
				}
				break;
			case 'u':
			case 'U':
				OutputDimensional(pStart);
				break;
			case 'e':
			case 'E':
				pStart = NULL;
				printf("Sie haben die gesammte Liste entfernt!\n");
				printf("Wollen sie von Vorne beginnen? [j/n]");
				scanf_s("%c", &begin);
				if (begin == 'j') {
					system("@cls||clear");
					main();
				}
				else if (begin == 'n') {
					return 0;
				}
				break;
			default:
				printf("Die Eingabe ist nicht Gueltig!\n\n");
				break; 
			}
		}
	}
}
