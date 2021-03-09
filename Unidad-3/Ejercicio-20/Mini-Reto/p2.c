#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


struct persona{
	char nombre[20];
	char ocupacion[20];
	int edad;
};

struct archivo{
	struct persona registros[100];
	int cant;
};

int main(int argc, char *argv[]) {

	sem_t *sem = sem_open("semFiles",0);

	if(sem == SEM_FAILED){
		perror("p1 sem_open fails: ");
		exit(EXIT_FAILURE);
	}

	if(sem_wait(sem)== -1){
		perror("pSemWait sem_wait fails: ");
		exit(EXIT_FAILURE);
	}

	struct archivo lista;
	lista.cant =0;

	FILE *fin = fopen(argv[2], "r");
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

	FILE *fout = fopen(argv[3], "w");
	if (fout == NULL) {
		perror("Error1: ");
		return EXIT_FAILURE;
	}

	for(int a=1;a<lista.cant;a++){
		for(int b = lista.cant-1;b>=a;b--){
			if(lista.registros[b-1].edad>lista.registros[b].edad){
				struct persona temp = lista.registros[b-1];
				lista.registros[b-1] = lista.registros[b];
				lista.registros[b] = temp;
			}
		}
	}

	for(int i = 0;i<lista.cant; i++){
		fprintf(fout,"%s %s %d\n", lista.registros[i].nombre,lista.registros[i].ocupacion,lista.registros[i].edad);
	}
	fclose(fout);

	if(sem_post(sem)== -1){
		perror("pSemCreate sem_wait fails: ");
		exit(EXIT_FAILURE);
	}

}


