#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex;
sem_t writeblock;
pthread_t rtid[20], wtid[20];

int data = 1;
int rc = 0;

void *readerFunc(void *arg) {
    int f = ((int *) arg); 
    sleep(rand()%2); 
    
    sem_wait(&mutex);
    rc++;
    if(rc==1)
    	sem_wait(&writeblock);
    
    sem_post(&mutex);
    printf("READER %d  |  DATA %d\n", f, data);
    sem_wait(&mutex);
    
    rc--;
    if(rc==0)
        sem_post(&writeblock);
    
    sem_post(&mutex);
}

void *writerFunc(void *arg) {
    int f = ((int *) arg); 
    sleep(rand()%2); 
    
    sem_wait(&writeblock);
    data = data + 2; 
    printf("WRITER %d  |  DATA %d\n", f, data);
    sem_post(&writeblock);
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);

	for(int i=0;i<50;i++) {
		int t = rand() % 20; 
		if (t%2==0) {
			pthread_create(&wtid[t] ,NULL, writerFunc, (void *) t);
			pthread_join(wtid[t] ,NULL);
		}

		else {
			pthread_create(&rtid[t] ,NULL, readerFunc, (void *) t);
			pthread_join(rtid[t] ,NULL);
		}
	}
}
