#include "stdlib.h"
#include "stdio.h"
#include "String.h"

struct Adresse {
	char firstname[50];
	char lastname[50];
	char street[50];
	char PLZ[50];
	char ort[50];

};

void main() {
	struct Adresse adresse;
	struct Adresse* pAdresse;

	strcpy_s(pAdresse->firstname, "Nevin");
	strcpy_s(pAdresse->lastname, "Helfenstein");
	strcpy_s(pAdresse->firstname, "Nevin");
	strcpy_s(pAdresse->firstname, "Nevin");
	strcpy_s(pAdresse->firstname, "Nevin");
	strcpy_s(pAdresse->firstname, "Nevin");

}