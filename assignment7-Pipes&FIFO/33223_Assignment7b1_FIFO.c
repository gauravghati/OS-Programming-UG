#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <string.h>

int main () {
    int fd1, fd2, i;
    char buf[512];
    int res = mkfifo("myfifo1",0777);
    if(res != 0)
        printf("\nError in creating FIFO\n");

    printf("Accept Sentences:");
    fgets(buf, 512, stdin);

    fd1 = open("myfifo1", O_WRONLY);
    write(fd1, buf, sizeof(buf));
    close(fd1);
    
    // 2nd process executes and send the data back

    res = mkfifo("myfifo2", 0777);
    if(res != 0)
        printf("\nError in creating FIFO\n");
    fd2=open("myfifo2", O_RDONLY);
    read(fd2, buf, sizeof(buf));
    close(fd2);

    printf("\nData received from pipe2 is:");    
    for(i=0; i<strlen(buf); i++)
        printf("%c",buf[i]);

    printf("\n"); 
    return 0;
}