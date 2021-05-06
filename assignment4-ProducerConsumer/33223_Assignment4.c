#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define BUFFER_SIZE 5

int buffer[10], indexB = 0;
sem_t full, empty;
pthread_t p[10], c[10];
pthread_mutex_t lock;

void printBuffer() {
	printf("\n");
	if(indexB!=0) {
		printf("Value of Buffer : ");
		for(int i = 0; i < indexB; i++)
			printf("%d ", buffer[i]);
	} else printf("\nBuffer Empty");

	printf("\n");
}

void* producer() {	
	while (true) {
		sem_wait(&empty);

		pthread_mutex_lock(&lock);
			int item = rand() % 100;
			buffer[indexB] = item;
			indexB++;
			printf("\nElement entered by producer is\t: %d ", item);
			printBuffer();
			float k = rand() % 3;
		pthread_mutex_unlock(&lock);

		sleep(k);
		sem_post(&full); 
	}
}

void* consumer() {
	while (true) {
		sem_wait(&full); 

		pthread_mutex_lock(&lock);
			indexB--; 
			printf("\nElement removed by consumer is\t: %d ", buffer[indexB]); 
			printBuffer();
			int k = rand() % 3;
		pthread_mutex_unlock(&lock);

		sleep(k);
		sem_post(&empty);
	}
}

void main() { 
	sem_init(&full, 0, 0); 
	sem_init(&empty,0, BUFFER_SIZE);
	pthread_mutex_init(&lock, NULL); 
	
	for(int i=0; i < 10; i++)  { 
		pthread_create(&p[i], NULL, &producer, NULL);
		pthread_create(&c[i], NULL, &consumer, NULL);
	} 
	
	for(int i = 0; i < 10; i++)  { 
		pthread_join(c[i], NULL);
		pthread_join(p[i], NULL);
	}

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&lock); 
	exit(0);
}

/*

Element entered by producer is	: 83 
Value of Buffer : 83 

Element entered by producer is	: 77 
Value of Buffer : 83 77 

Element entered by producer is	: 93 
Value of Buffer : 83 77 93 

Element entered by producer is	: 86 
Value of Buffer : 83 77 93 86 

Element removed by consumer is	: 86 
Value of Buffer : 83 77 93 

Element removed by consumer is	: 93 
Value of Buffer : 83 77 

Element entered by producer is	: 62 
Value of Buffer : 83 77 62 

Element removed by consumer is	: 62 
Value of Buffer : 83 77 

Element entered by producer is	: 59 
Value of Buffer : 83 77 59 

Element entered by producer is	: 26 
Value of Buffer : 83 77 59 26 

Element removed by consumer is	: 26 
Value of Buffer : 83 77 59 

Element removed by consumer is	: 59 
Value of Buffer : 83 77 

Element removed by consumer is	: 77 
Value of Buffer : 83 

Element entered by producer is	: 11 
Value of Buffer : 83 11 

Element entered by producer is	: 67 
Value of Buffer : 83 11 67
.
.
.
.
.
.
.
.

*/