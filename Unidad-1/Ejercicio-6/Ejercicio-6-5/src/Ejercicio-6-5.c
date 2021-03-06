/*
 ============================================================================
 Name        : Ejercicio-6-5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct estudiante {
	char Nombre[40];
	int numEstudiante;
	int agnoEstudiante;
	float nota;
};

void imprimirEstudiante(struct estudiante *ptrEstruct);

int main(void) {
	struct estudiante estud1 = { "Jose1", 4, 2009, 4.5 };
	struct estudiante *ptrEstruct;
	ptrEstruct = &estud1;
	imprimirEstudiante(ptrEstruct);
	if (getchar() == 'r') {
		printf("Ingrese el nombre del estudiante\n");
		scanf("%s", ptrEstruct->Nombre);
		printf("Ingrese el numero del estudiante\n");
		scanf("%d", &ptrEstruct->numEstudiante);
		printf("Ingrese el año del estudiante\n");
		scanf("%d", &ptrEstruct->agnoEstudiante);
		printf("Ingrese la nota del estudiante\n");
		scanf("%f", ptrEstruct->nota);
		imprimirEstudiante(ptrEstruct);
	}
	return 0;
}

void imprimirEstudiante(struct estudiante *ptrEstruct) {
	printf("La nota del estudiante %s con numero %d y año %d es %.2f \n",
			ptrEstruct->Nombre, ptrEstruct->numEstudiante,
			ptrEstruct->agnoEstudiante, ptrEstruct->nota);
}
