#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

#define SH_SIZE 16

int shared_fd = -1;
char mem[20];
int32_t *counter = NULL;
sem_t *semaphore = NULL;
sem_t *semaphore1 = NULL;

void init_control_mechanism() {
	semaphore = sem_open("sem0", O_CREAT, 0666, 0);
	if (semaphore == SEM_FAILED) {
		perror("Opening the semaphore failed: ");
		exit(EXIT_FAILURE);
	}
	semaphore1 = sem_open("sem1", O_CREAT, 0666, 0);
	if (semaphore == SEM_FAILED) {
		perror("Opening the semaphore failed: ");
		exit(EXIT_FAILURE);
	}
}

void shutdown_control_mechanism() {
	if (sem_close(semaphore) < 0) {
		perror("Closing the semaphore failed: ");
		exit(EXIT_FAILURE);
	}

	if (sem_unlink("sem0") < 0) {
		perror("Unlinking failed: ");
		exit(EXIT_FAILURE);
	}
}

void lectura(char *mem) {
	while (1) {
		sem_wait(semaphore1);
		if(!strcmp(mem,"exit")) {
			printf("Proceso hermano cerrado\n");
			break;
		}
		printf("ACK: %s \n",mem);
	}
}

void escritura(char *mem) {
	while (1) {
		char a[20];
		scanf("%[^\n]", a);
		getchar();
		strcpy(mem,a);
		sem_post(semaphore);
		if(!strcmp(mem,"exit")) break;
	}
}

void init_shared_resource() {
	shared_fd = shm_open("shm0", O_CREAT | O_RDWR, 0777);
	if (shared_fd < 0) {
		perror("Failed to create shared memory: ");
		exit(EXIT_FAILURE);
	}
}

void shutdown_shared_resource() {
	if (shm_unlink("/shm0") < 0) {
		perror("Unlinking shared memory failed: ");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv) {
	init_control_mechanism();
	sem_wait(semaphore1);
	init_shared_resource();

	if (ftruncate(shared_fd, SH_SIZE * sizeof(char)) < 0) {
		perror("Truncation failed: ");
		exit(EXIT_FAILURE);
	}
	void *map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);

	if (map == MAP_FAILED) {
		perror("Mapping failed: ");
		exit(EXIT_FAILURE);
	}
	char* mem = (char*)map;

	printf("ready\n");
	sem_post(semaphore);

	pthread_t hilo1;
	pthread_t hilo2;

	pthread_create(&hilo1, NULL, (void*) lectura, (void*) mem);
	pthread_create(&hilo2, NULL, (void*) escritura, (void*) mem);
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);



	shutdown_control_mechanism();

	exit(EXIT_SUCCESS);
}
