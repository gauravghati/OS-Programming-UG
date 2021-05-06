#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
# define MAX 20

pthread_mutex_t wrt;
pthread_mutex_t mutex;
pthread_t rtid, wtid;

int data = 1;
int rc = 0; 

void* readerFunc(void *arg) {
	while(true) {
		pthread_mutex_lock(&mutex);
		rc++;
		if(rc==1)
			pthread_mutex_lock(&wrt);
		pthread_mutex_unlock(&mutex);
		printf("READER read the DATA: %d\n", data+1);
		pthread_mutex_lock(&mutex);
		rc--;
		if(rc==0)
			pthread_mutex_unlock(&wrt);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%2);
	}
}

void* writerFunc(void *arg) {
	while(true) {
		pthread_mutex_lock(&wrt);
		data = data + 1;
		printf("WRITER changed DATA to: %d\n", data+1);
		pthread_mutex_unlock(&wrt);
		sleep(rand()%2);
	}
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

	pthread_create(&wtid, NULL, &writerFunc, NULL);
	pthread_create(&rtid, NULL, &readerFunc, NULL);

	pthread_join(wtid, NULL);
	pthread_join(rtid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);
	exit(0);
}
