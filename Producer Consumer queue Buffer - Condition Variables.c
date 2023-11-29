#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<pthread.h>

#define BUFFER_SIZE 20

int buffer[20], head = -1, tail = -1;
pthread_t worker;
pthread_mutex_t lock;
pthread_cond_t space_avail, item_avail;
bool done = false;

int buffer_full() {
    return (tail + 1) % BUFFER_SIZE == head;
}

int buffer_empty() {
    return head == -1;
}

void printBuffer() {
    printf("\nQueue elements: ");
    if (buffer_empty()) {
        printf("\n");
        return;
    }

    int i = head;
    do {
        printf("%d ", buffer[i]);
        i = (i + 1) % BUFFER_SIZE;
    } while (i != (tail + 1) % BUFFER_SIZE);
    printf("\n");
}

void producer(int item) {	
    pthread_mutex_lock(&lock);
        while(buffer_full())
            pthread_cond_wait(&space_avail, &lock);
        
        if(buffer_empty())
            head = 0;

        tail = (tail + 1) % BUFFER_SIZE;
        buffer[tail] = item;
        printf("\nElement entered by producer is\t: %d ", item);
        printBuffer();
        pthread_cond_signal(&item_avail);   
        
        int k = rand() % 3;
        sleep(k);

    pthread_mutex_unlock(&lock);
}

void* consumer() {
	while (!done) {
        pthread_mutex_lock(&lock);
            while(buffer_empty())
                pthread_cond_wait(&item_avail, &lock);

            int item = buffer[head];
            if (head == tail) {
                head = tail = -1;
            } else {
                head = (head + 1) % BUFFER_SIZE;
            }
            printf("\nElement removed by consumer is\t: %d ", item);
            printBuffer();
            pthread_cond_signal(&space_avail);

            int k = rand() % 3;
            sleep(k);

        pthread_mutex_unlock(&lock);
	}
}

int main() {
	pthread_mutex_init(&lock, NULL); 
    pthread_cond_init(&space_avail, NULL);
    pthread_cond_init(&item_avail, NULL);

    pthread_create(&worker, NULL, &consumer, NULL);

    for(int i = 0; i < 25; i++)
        producer(30 + i);
    done = true;

    pthread_join(worker, NULL);

	pthread_mutex_destroy(&lock); 
    pthread_cond_destroy(&item_avail);
    pthread_cond_destroy(&space_avail);

	return 0;
}
