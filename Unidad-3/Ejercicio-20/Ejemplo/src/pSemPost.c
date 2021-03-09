#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int args, char *argv[]) {

	sem_t *sem = sem_open("semExample",0);

	if(sem == SEM_FAILED){
		perror("pSemPost sem_open fails: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemPost %d sem_post() ...\n",getpid());
	if(sem_post(sem)== -1){
		perror("pSemCreate sem_wait fails: ");
		exit(EXIT_FAILURE);
	}
	printf("pSemPost %d succeeded ...\n",getpid());

	if(sem_close(sem) == -1){
		perror("pSemPost sem_close fails: ");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
