/*
 ============================================================================
 Name        : Ejercicio-3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t glob_mutex;
static long glob = 0;

static void* threadFunc(void *arg) {
    int loops = *((int *) arg);
    long loc;

    for (int j = 0; j < loops; j++) {
    	pthread_mutex_lock(&glob_mutex);
        loc = glob;
        loc++;
        glob = loc;
        pthread_mutex_unlock(&glob_mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t t1, t2;
    int loops, s;
    pthread_mutex_init(&glob_mutex,NULL);

    loops = (argc > 1) ? atol(argv[1]) : 10000000;

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");

    s = pthread_join(t1, NULL);
    if (s != 0) perror("pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0) perror("pthread_join");

    printf("glob = %ld\n", glob);
    exit(EXIT_SUCCESS);
}
