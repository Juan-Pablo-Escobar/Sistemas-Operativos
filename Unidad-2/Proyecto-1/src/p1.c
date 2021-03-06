
#include <stdio.h>
#include <stdlib.h>

struct node{
	char key[20];
	int value;
};


int main1(int argc, char *argv[]) {
	if(argc == 3){

		struct node lista[100];
		int cant=0;

		FILE *fin = fopen(argv[1], "r");
		if (fin == NULL) {
		    perror("Error: ");
		    return EXIT_FAILURE;
		}

		while ( fscanf(fin,"%s %d", lista[cant].key,&lista[cant].value) == 2) {
			cant++;
		}
		fclose(fin);

		FILE *fout = fopen(argv[2], "w");
		if (fout == NULL) {
		    perror("Error: ");
		    return EXIT_FAILURE;
		}

		for(int a=1;a<cant;a++){
			for(int b = cant-1;b>=a;b--){
				if(lista[b-1].value>lista[b].value){
					struct node temp = lista[b-1];
					lista[b-1] = lista[b];
					lista[b] = temp;
				}
			}
		}

		for(int i = 0;i<cant; i++){
			fprintf(fout,"%s %d\n", lista[i].key,lista[i].value);
		}
		fclose(fout);

	}else{
		return 1;
	}
}
