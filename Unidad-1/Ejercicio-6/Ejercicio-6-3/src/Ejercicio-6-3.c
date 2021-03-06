/*
 ============================================================================
 Name        : Ejercicio-6-3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct cdsMusica{
	char titulo[40];
	char artista[40];
	char genero[15];
	int numCanciones;
	int lanzamiento;
	int precio;
};


int main(void) {
	struct cdsMusica cds = {"Brindo con el alma","Diomedes Diaz","Vallenato",11,1986,19900};
	printf("titulo: %s\nartista: %s\ngenero: %s\nnumCanciones: %d\nlanzamiento: %d\nprecio: %d",cds.titulo,cds.artista,cds.genero,cds.numCanciones,cds.lanzamiento,cds.precio);
}
