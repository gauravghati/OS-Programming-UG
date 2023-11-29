#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

#define BUFFER_SIZE 30
#define BLOCK_SIZE 12

char buffer[BUFFER_SIZE], head = -1, tail = -1;
pthread_t worker;
pthread_mutex_t lock;
pthread_cond_t space_avail, item_avail;
bool done = false;

int buffer_full() {
    return (tail + 1) % BUFFER_SIZE == head;
}

int buffer_empty() {
    return (head == -1);
}

int buffer_used() {
    if(head == -1) return 0;
    int val = (tail >= head) ? (tail - head):((BUFFER_SIZE - head) + tail);
    return val + 1; 
}

void printBuffer() {
    printf("\nQueue elements: ");
    if (buffer_empty()) {
        printf(" Empty\n");
        return;
    }
    for(int i = 0; i < buffer_used(); i++) {
        printf("%c ", buffer[ (head + i) % BUFFER_SIZE]);
    }

    printf("\n");
    printf("Head :: %d, Tail :: %d, buffer size :: %d \n", head, tail, buffer_used());
}

void producer(char *item) {	
    pthread_mutex_lock(&lock);
        printf("Producer mutex locked\n");
        while(buffer_full()) {
            printf("Producer waiting for space available\n");
            pthread_cond_wait(&space_avail, &lock);            
        }
        
        if(buffer_empty())
            head = 0;

        for(int i = 0; i < strlen(item); i++) {
            tail = (tail + 1) % BUFFER_SIZE;
            buffer[tail] = item[i];
        }
        printf("\nElement entered by producer is\t: %s \n", item);
        printBuffer();
        sleep(rand() % 2);
        pthread_cond_signal(&item_avail);

    pthread_mutex_unlock(&lock);
    printf("Producer mutex unlocked\n");
}

void* consumer() {
	while (!done) {
        pthread_mutex_lock(&lock);
            printf("Consumer mutex locked\n");
            while(buffer_empty() || BLOCK_SIZE >= buffer_used()) {
                if(done) break;
                printf("Consumer waiting for item\n");
                pthread_cond_wait(&item_avail, &lock);
            }

            if(done) {
                printBuffer();
                pthread_mutex_unlock(&lock);
                break;
            }

            char *item = (char *) malloc(sizeof(BLOCK_SIZE));
            
            for(int i = 0; i < BLOCK_SIZE; i++) {
                item[i] = buffer[(head + i) % BUFFER_SIZE];
            }

            if (head == tail) {
                head = tail = -1;
            } else {
                head = (head + BLOCK_SIZE) % BUFFER_SIZE;
            }

            printf("\nElement removed by consumer is\t: %s ", item);

            printBuffer();
            pthread_cond_signal(&space_avail);
            sleep(rand() % 2);

        pthread_mutex_unlock(&lock);
        printf("Consumer mutex unlocked\n");
	}
}

char* generateRandomString(int length) {
    char *str = (char *) malloc(sizeof(length));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charsetSize = sizeof(charset) - 1;

    srand((unsigned int)time(NULL));
    
    str[0] = '|';
    for (int i = 1; i < length; ++i) {
        str[i] = charset[rand() % charsetSize];
    }

    str[length] = '\0';
    return str;
}

int main() {
	pthread_mutex_init(&lock, NULL); 
    pthread_cond_init(&space_avail, NULL);
    pthread_cond_init(&item_avail, NULL);

    pthread_create(&worker, NULL, &consumer, NULL);

    for(int i = 0; i < 25; i++) {
        char *val = generateRandomString((rand() % 5) + 2);
        sleep(rand() % 2);
        producer(val);
    }
    done = true;

    pthread_join(worker, NULL);

	pthread_mutex_destroy(&lock); 
    pthread_cond_destroy(&item_avail);
    pthread_cond_destroy(&space_avail);
	return 0;
}
