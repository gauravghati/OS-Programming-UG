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
        close(fd[0]); // close read of pipe
        int x;
        printf("Input a number: "); 
        scanf("%d", &x); 
        write(fd[1], &x, sizeof(int)); // write to fd[1]
        close(fd[1]); // close write of pipe
    } else {
        close(fd[1]); // close write
        int y; 
        read(fd[0], &y, sizeof(int));  // read from fd[0]
        close(fd[0]);           // close read
        printf("Got from child process: %d\n", y); 
    }
    return 0; 
}