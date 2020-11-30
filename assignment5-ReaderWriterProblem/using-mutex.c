#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t writeback;
pthread_mutex_t mutex;
pthread_t rtid[20], wtid[20];

int data = 1;
int rc = 0;

void *readerFunc(void *arg) {
	int f = ((int *) arg); 
	sleep(rand()%3);

	pthread_mutex_lock(&mutex);

	rc++;
	if(rc==1)
		pthread_mutex_lock(&writeback);
	pthread_mutex_unlock(&mutex);

	printf("READER %d  |  DATA: %d\n", f, data);
	sleep(rand()%3);
	pthread_mutex_lock(&mutex);
	
	rc--;
	if(rc==0)
		pthread_mutex_unlock(&writeback);
		
	pthread_mutex_unlock(&mutex);
}

void *writerFunc(void *arg) {
	int f = ((int *) arg); 
 	sleep(rand()%3);

	pthread_mutex_lock(&writeback);
	data = data * 2; 
	printf("WRITER %d  |  DATA %d\n", f, data);
    	pthread_mutex_unlock(&writeback);
}

int main() {
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&writeback,NULL);

    for(int i=0;i<20;i++) {
        pthread_create(&wtid[i] ,NULL, writerFunc, (void *) i);
        pthread_create(&rtid[i] ,NULL, readerFunc, (void *) i);
    }

    for(int i=0;i<20;i++) {
        pthread_join(wtid[i] ,NULL);
        pthread_join(rtid[i] ,NULL);
    }
}
