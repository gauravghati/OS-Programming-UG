#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
//#include <cstdlib>
#define MAX 20

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int t;
    t=*a; *a=*b; *b=t;
}
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
    if (arr[j] > arr[j+1])
    swap(&arr[j], &arr[j+1]);
}
void heapify(int arr[], int n, int i) {
    int largest = i; 
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i=n-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int process_id, size, array[30], i, choice, search, temp[20];
    char str[30];
    char *arg[30];
    
    printf("\nENTER SIZE OF ARRAY : ");
    scanf("%d", &size);
    
    printf("\nENTER ARRAY ELEMENTS : ");
    for(i=0; i<size; i++)
        scanf("%d", &array[i]);
    
    printf("\nENTER ELEMENT TO BE SEARCHED : ");
    scanf("%d", &search);
    //bubbleSort(array, size);
    
    printf("\nMENU : \n1)HEAP SORT\n2)BUBBLE SORT\nENTER YOUR CHOICE : ");
    scanf("%d", &choice);

    process_id = fork();
    printf("\nFORK DONE");

    switch(process_id) {
        case -1 : 
            printf("\n\tERROR!");
            break;

        case 0 : 
            printf("\n\n\t===========CHILD BLOCK=============");
            printf("\n\tCHILD ID : %d", getpid());
            printf("\n\tPARENT ID : %d", getppid());
            switch(choice) {
                case 1 : printf("\n\tHEAP SORT");
                heapSort(array, size);
                break;
                case 2 : printf("\n\tBUBBLE SORT");
                bubbleSort(array, size);
                break;
            }
            printf("\n\tSORTED ARRAY(CHILD) : ");
            printArray(array, size);
            for(i=0; i<size; i++)
            temp[i] = array[i];
            temp[i] = search;
            for(i=0; i<size+1; i++) {
                sprintf(str, "%d", temp[i]);
                arg[i] = malloc(sizeof(str));
                strcpy(arg[i], str);
            }
            arg[i]=NULL;
            execve("./bsearch", arg, NULL);
            break;
        
        default : 
            printf("\n\n\t===========PARENT BLOCK=============");
            printf("\n\tPARENT ID : %d", getpid());
            switch(choice) {
                case 1 : printf("\n\tHEAP SORT");
                heapSort(array, size);
                break;
                case 2 : printf("\n\tBUBBLE SORT");
                bubbleSort(array, size);
                break;
            }
            printf("\n\tSORTED ARRAY(PARENT) : ");
            printArray(array, size);
            break;
    }
    return 0;
}