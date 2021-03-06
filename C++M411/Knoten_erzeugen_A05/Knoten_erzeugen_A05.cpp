// Knoten_erzeugen_A05.cpp : Defines the entry point for the console application.
//
#include "stdlib.h"
#include "stdio.h"
#include "String.h"
#include "stdafx.h"

struct Element {
	int Nummer;
	struct Element* pNext;
};

typedef struct Element struElm;

void Output(struElm* pStart) {
	//Gibt Liste aus
	printf("Liste:\n\n");
	for (struElm* pOut = pStart; pOut != NULL; pOut = pOut->pNext)
		printf("%i\n", pOut->Nummer);
}

struElm* Create(int Anzahl) {
	//Erstellt eine Liste von definierter Anzahl Elemente
	struElm* pStart = NULL;
	struElm* pLast = NULL;

	for (int iElm = 0; iElm < Anzahl; iElm++) {
		struElm* pNew = (struElm*)malloc(sizeof(struElm));
		pNew->Nummer = iElm + 1;
		pNew->pNext = NULL;
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
	}
	return pStart;
}

int main()
{
	struElm* pStart = Create(5);
	Output(pStart);
	system("pause");
}

