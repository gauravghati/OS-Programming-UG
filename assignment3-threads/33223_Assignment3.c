#include<pthread.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int matrix1[10][10],matrix2[10][10],row1,col1,col2,row2;

void input(int matrix[10][10],int row,int col) {
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            scanf("%d", &matrix[i][j]);
}

void print(int matrix[10][10],int row,int col) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

void* multiply(void *arg) {
    int p= (int)arg;
    printf("\nINSIDE MULT THREAD %d\n",p+1);

    int* q =(int*) malloc(sizeof(int)*col2);
    for(int i=0;i<col2;i++) {
        int result=0;
        for(int j=0;j<col1;j++)
            result = result + matrix1[p][j]*matrix2[j][i];
        q[i]=result;
    }
    pthread_exit(q);
}

int main()
{
    int res;
    int* p;

    printf("ENTER NUMBER OF ROWS FOR MATRIX 1:");
    scanf("%d",&row1);

    printf("ENTER NUMBER OF COLUMNS FOR MATRIX 1:");
    scanf("%d",&col1);
    printf("ENTER NUMBER OF ROWS FOR MATRIX 2:");
    scanf("%d",&row2);
    printf("ENTER NUMBER OF COLUMNS FOR MATRIX2:");
    scanf("%d",&col2);
    
    if(col1==row2) {
        pthread_t thread[row1];
        printf("\nENTER ELEMENTS FOR MATRIX 1:\n");
        input(matrix1,row1,col1);
        printf("\nENTER ELEMENTS FOR MATRIX 2:\n");
        input(matrix2,row2,col2);
        printf("\nMATRIX 1\n");
        print(matrix1,row1,col1);
        printf("\nMATRIX 2\n");
        print(matrix2,row2,col2);
        printf("RESULTANT MULTIPLICATION MATRIX\n");

        for(int i=0;i<row1;i++) {
            res = pthread_create(&thread[i], NULL, &multiply, (void*) i);
            if(res){ printf("Error occured while creating thread %d", i); break; }
        }
        for(int j=0;j<row1;j++) {
            res = pthread_join(thread[j], (void**) &p);
            if(res){ printf("Error occured while joining thread %d", j); break; }
            printf("\n");
            for(int i=0;i<col2;i++)
                printf("%d ",*(p+i));
        }
    }
    else
        printf("MULTIPLICATION NOT POSSIBLE");
}

/*
    1) pthread_create(p1, p2, p3, p4);
    p1 => thread pointer
    p2 => thread customization
    p3 => function pointer
    p4 => function parameters (void pointer only)

    2) pthread_join(p1, p2);
    p1 => thread
    p2 => pointer of returned value

*/