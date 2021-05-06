#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>

#define CONSUMED_BY_CLIENT -1
#define DATA_IS_NOT_FILLED_BY_SERVER 0
#define DATA_FILLED_BY_SERVER 1
#define CONSUMED_BY_SERVER 2
#define DATA_IS_NOT_FILLED_BY_CLIENT 3
#define DATA_FILLED_BY_CLIENT 4

typedef struct mem {
    int status;
    char data[];
} SHARED_MEMORY;

int main()
{
    SHARED_MEMORY *shm_ptr;
    int shmid;
    char value[100];
    key_t key = ftok(".", 1);

    shmid = shmget(key, sizeof(SHARED_MEMORY), IPC_CREAT | 0666);
    if(shmid == -1)
        printf("\nError In Creating Shared Memory\n");
    else
        printf("\nShared Memory Created\n");
        
    shm_ptr = shmat(shmid, NULL, 0);

    if(shm_ptr->status == -1)
        printf("\nError In Attaching To The Memory\n");
    else
        printf("Attached To The Shared Memory\n");
    
    shm_ptr->status = DATA_IS_NOT_FILLED_BY_SERVER;
    printf("\nWrite a message:\n");
    scanf("%[^\n]", value);
    printf("\nMessage sent to CLIENT\n");
    strcpy(shm_ptr->data, value);
    shm_ptr->status = DATA_FILLED_BY_SERVER;

    while(shm_ptr->status != CONSUMED_BY_CLIENT)    {
        printf("\nWaiting for CLIENT to read...\n");
        sleep(5);
    }
    while(shm_ptr->status != DATA_FILLED_BY_CLIENT)    {
        printf("\nWating For CLIENT to respond...\n");
        sleep(5);
    }
    printf("\nMessage recieved from CLIENT:\n");
    printf("%s\n",shm_ptr->data);

    shm_ptr->status = CONSUMED_BY_SERVER;
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, 0);
    printf("\nExiting the SERVER Program\n");
    return 0;
}