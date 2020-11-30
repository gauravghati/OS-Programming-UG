#include <stdio.h>

int main(int argnum, char* paras[]) {
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    int res = pipe(fd);
    if (res == -1) {
        printf("Error Occur with opening a pipe"); 
        return 1; 
    }
    int id = fork();  
    if (id==0) {
        close(fd[0]); 
        int x;
        printf("Input a number: "); 
        scanf("%d", &x); 
        write(fd[1], &x, sizeof(int)); 
        close(fd[1]); 
    } else {
        close(fd[1]);
        int y; 
        read(fd[0], &y, sizeof(int)); 
        close(fd[0]); 
        printf("Got from child process: %d\n", y); 
    }
    return 0; 
}