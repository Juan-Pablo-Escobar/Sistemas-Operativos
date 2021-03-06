
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int mypid = getpid();
	int pid[3];
	int id=0;
	for(int i = 0;i<2;i++){
		pid[i] = fork();
		if(getpid() != mypid){
			id = i+1;
			break;
		}
	}

	if(id==1){
		char *args[]={"./p1",argv[1],argv[2],NULL};
		execv(args[0],args);
	}else if(id==2){
		char *args[]={"./p2",argv[1],argv[3],NULL};
		execv(args[0],args);
	}else if(id == 0){
		printf("Process %d terminated\n",wait(NULL));
		printf("Process %d terminated\n",wait(NULL));

		printf("\nLectura del archivo p1 %s\n\n",argv[2]);

		FILE *fin = fopen(argv[2], "r");
		if (fin == NULL) {
			perror("Error: ");
			return EXIT_FAILURE;
		}
		char clave[20];
		int valor = 0;

		while ( fscanf(fin,"%s %d", clave,&valor) == 2) {
			printf("%s %d\n", clave,valor);
		}
		fclose(fin);

		printf("\nLectura del archivo p2 %s\n\n",argv[2]);

		FILE *fin1 = fopen(argv[3], "r");
		if (fin == NULL) {
			perror("Error: ");
			return EXIT_FAILURE;
		}
		char clave1[20];
		int valor1 = 0;

		while ( fscanf(fin1,"%s %d", clave1,&valor1) == 2) {
			printf("%s %d\n", clave1,valor1);
		}
		fclose(fin);

	}


	return EXIT_SUCCESS;
}
