#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int args, char *argv[]) {

	mode_t perms = 0666;
	int flags = O_CREAT;


	unsigned int value = 0;

	sem_t *sem = sem_open("semExample",flags,perms,value);

	if(sem == SEM_FAILED){
		perror("pSemCreate sem_open fails: ");
		exit(EXIT_FAILURE);
	}

	if(sem_close(sem) == -1){
		perror("pSemCreate sem_close fails: ");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
