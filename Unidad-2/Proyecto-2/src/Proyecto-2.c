/*
 ============================================================================
 Name        : Proyecto-2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct persona{
	char nombre[20];
	char ocupacion[20];
	int edad;
};

struct archivo{
	struct persona registros[100];
	int cant;
};

struct hilo_param{
	struct archivo archivo;
	char outfile[20];
};

int p_hilo2(struct hilo_param* hilo2_param) {


	char outfile[20];
	strcpy(outfile,hilo2_param->outfile);
	printf("archivo %s",outfile);
	struct archivo archivo = hilo2_param->archivo;

	FILE *fout = fopen(outfile, "w");
	if (fout == NULL) {
		perror("Error1: ");
		return EXIT_FAILURE;
	}

	for(int a=1;a<archivo.cant;a++){
		for(int b = archivo.cant-1;b>=a;b--){
			if(strcmp(archivo.registros[b-1].ocupacion,archivo.registros[b].ocupacion)>0){
				struct persona temp = archivo.registros[b-1];
				archivo.registros[b-1] = archivo.registros[b];
				archivo.registros[b] = temp;
			}
		}
	}

	for(int i = 0;i<archivo.cant; i++){
		fprintf(fout,"%s %s %d\n", archivo.registros[i].nombre,archivo.registros[i].ocupacion,archivo.registros[i].edad);
	}
	fclose(fout);
	return 0;

}

int p_hilo1(struct hilo_param* hilo1_param) {

	char outfile[20];
	strcpy(outfile,hilo1_param->outfile);
	struct archivo archivo = hilo1_param->archivo;

	FILE *fout = fopen(outfile, "w");
	if (fout == NULL) {
		perror("Error: ");
		return EXIT_FAILURE;
	}

	for(int i = archivo.cant-1;i>=0; i--){
		fprintf(fout,"%s %s %d\n", archivo.registros[i].nombre,archivo.registros[i].ocupacion,archivo.registros[i].edad);
	}
	fclose(fout);
	return 0;

}

int main(int argc, char *argv[]) {

	struct archivo lista;
	lista.cant =0;

	FILE *fin = fopen(argv[1], "r");
	if (fin == NULL) {
		perror("Error: ");
		return EXIT_FAILURE;
	}

	while ( fscanf(fin,"%s %s %d", lista.registros[lista.cant].nombre,lista.registros[lista.cant].ocupacion,&lista.registros[lista.cant].edad) == 3) {
		lista.cant++;
	}
	fclose(fin);

	for(int i=0;i<lista.cant;i++){
		printf("%s %s %d\n", lista.registros[i].nombre,lista.registros[i].ocupacion,lista.registros[i].edad);
	}

	struct hilo_param hilo1_param;
	hilo1_param.archivo = lista;
	strcpy(hilo1_param.outfile,argv[2]);

	struct hilo_param hilo2_param;
	hilo2_param.archivo = lista;
	strcpy(hilo2_param.outfile,argv[3]);

	pthread_t hilo1;
	pthread_t hilo2;

	pthread_create(&hilo1,NULL,(void*)p_hilo1,&hilo1_param);
	pthread_create(&hilo2,NULL,(void*)p_hilo2,&hilo2_param);
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);

	return EXIT_SUCCESS;
}
