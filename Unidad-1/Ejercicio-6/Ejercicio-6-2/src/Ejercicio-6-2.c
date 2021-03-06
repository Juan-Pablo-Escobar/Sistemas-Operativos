/*
 ============================================================================
 Name        : Ejercicio-6-2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


struct materia{
	char nombre[20];
	int creditos;
	float nota;
};

int main(void) {
	int a;
	printf("Ingrese numero de materias\n");
	scanf("%d", &a);
	fflush(stdin);
	struct materia *materias;
	materias = malloc(sizeof(struct materia)*a);

	for(int i =0;i<a;i++){
		printf("Materia %d \nIngrese nombre de la materia numero %d\n",i+1,i+1);
		scanf("%s", &materias[i].nombre);
		printf("Ingrese su nota en la materia: %s\n",&materias[i].nombre);
		scanf("%f", &materias[i].nota);
		printf("Ingrese el valor credito de la materia: %s\n",&materias[i].nombre);
		scanf("%d", &materias[i].creditos);
	}

	float sum1= 0.0;
	int sum2 = 0;
	printf("%-22s%-8s%s\n","Materias","nota","creditos");
	for(int i=0;i<a;i++){
		printf("%-22s%-8.1f%d\n",&materias[i].nombre,materias[i].nota,materias[i].creditos);
		sum1 += (materias[i].nota*materias[i].creditos);
		sum2 += (materias[i].creditos);
	}
	printf("%-30s%.3f","promedio ponderado",sum1/sum2);

}



