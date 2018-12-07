#include "stdlib.h"
#include "stdio.h"
#include "String.h"

typedef struct Element {
	int Nummer;
	struct Element* pNext;
}struElement;
//typedef struct Element struElement;

void main() {
	struElement *pStart = NULL;

	for (int i = 10; i > 0; i--) {
		//struct Element *pEelement = (struct Element*) malloc(sizeof(struct Element));
		struElement *pElement = (struElement*)malloc(sizeof(struElement));
		pElement->Nummer = i;
		pElement->pNext = pStart;
		pStart = pElement;
	}

	for (struElement *pOut = pStart; pOut != NULL; pOut = pOut->pNext) {
		printf("Element: %i\n", pOut->Nummer);
	}

	system("pause");
}