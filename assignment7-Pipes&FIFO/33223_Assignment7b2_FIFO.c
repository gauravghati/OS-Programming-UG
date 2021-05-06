#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int fd2, fd1, chars=0, words=0;
    char buf[512],str[512];

    fd1=open("myfifo1",O_RDONLY);
    read(fd1, buf, sizeof(buf));

    //2
    printf("\nData received is:\n");
    for(int i=0; i<strlen(buf); i++)
        printf("%c", buf[i]);

    close(fd1);
    
    //2 Count characters, words , lines
    for(int i=0; i<strlen(buf); i++)
        if(buf[i]==' ')
            words++;

    words++;
    chars=strlen(buf)-words-1;
    fd2=open("myfifo2",O_WRONLY); //3
    
    //4
    sprintf(str, "\nNumber of words:%d\nNumber of characters: %d", words, chars+1);
    
    //5
    write(fd2, str, sizeof(str));
    close(fd2);
    return 0;
}