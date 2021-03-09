#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int args, char *argv[]) {

	sem_t *sem = sem_open("semExample",0);

	if(sem == SEM_FAILED){
		perror("pSemWait sem_open fails: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d sem_wait() ...\n",getpid());
	if(sem_wait(sem)== -1){
		perror("pSemWait sem_wait fails: ");
		exit(EXIT_FAILURE);
	}

	printf("pSemWait %d succeeded ...\n",getpid());
	if(sem_close(sem) == -1){
		perror("pSemWait sem_close fails: ");
		exit(EXIT_FAILURE);
	}

	if(sem_unlink("semExample") == -1){
		perror("pSemWait sem_unlink fails: ");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
