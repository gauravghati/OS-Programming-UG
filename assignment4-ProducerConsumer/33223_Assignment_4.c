#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define BUFFER_SIZE 5

int buffer[10],indexB = 0;
int a,b;
sem_t full, empty;
pthread_t p,c;
pthread_mutex_t lock;

void printBuffer() {
	bool flag = true;
	printf("\n");
	printf("Value of Buffer : ");
	for(int i = 0; i < indexB; i++) {
		printf("%d ",buffer[i]);
		flag = false;
	}
	printf("\n");
	if(flag)
		printf("\nBuffer Empty\n");
}

void *producer() {	
	while (1) {
		sem_wait(&full);
		pthread_mutex_lock(&lock);

		int item = rand() % 100;
		if(indexB < BUFFER_SIZE)  { 
			buffer[indexB] = item; 
			indexB++; 
			printf("\nElement entered by producer is\t: %d ",item); 
		} 
		else printf("\nBuffer full"); 

		printBuffer();
		float k = rand() % 5;
		pthread_mutex_unlock(&lock);
		sleep(k);
		sem_post(&empty); 
	}
}

void *consumer() {
	while (1) {
		sem_wait(&empty); 
		pthread_mutex_lock(&lock);
		
		if(indexB > 0)  { 
			indexB--; 
			printf("\nElement removed by consumer is\t: %d ",buffer[indexB]); 
		} 
		else printf("\n*Buffer is empty*"); 

		printBuffer();
		int k = rand() % 5;
		pthread_mutex_unlock(&lock);
		sleep(k);
		sem_post(&full);	
	}
}
	 	 
void main() { 
	sem_init(&full,1,BUFFER_SIZE); 
	sem_init(&empty,1,0);
	pthread_mutex_init(&lock,NULL); 
	
	// for(int i=0; i < 10; i++)  { 
		pthread_create(&p,NULL,producer,NULL);
		pthread_create(&c,NULL,consumer,NULL);
	//	} 
	
	//	for(int i = 0; i < 10; i++)  { 
		pthread_join(c,NULL); 
		pthread_join(p,NULL); 	 
	//	}
	exit(0);
}
