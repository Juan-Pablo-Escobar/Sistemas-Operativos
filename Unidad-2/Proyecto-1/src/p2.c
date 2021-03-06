#include <stdio.h>
#include <stdlib.h>

struct node{
	char key[20];
	int value;
};


int main2(int argc, char *argv[]) {
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

		for(int i = cant-1;i>=0; i--){
			fprintf(fout,"%s %d\n", lista[i].key,lista[i].value);
		}
		fclose(fout);

	}else{
		return 1;
	}
}
