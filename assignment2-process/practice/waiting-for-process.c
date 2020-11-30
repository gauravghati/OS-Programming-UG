#include <stdio.h>
#include <unistd.h>

int main(void) {
	int id = fork();
    int num=0; 

	if (id == -1)
		printf("Error occur at the time of creation\n");
	else if(id==0)
		num = 1; 
    else
		num = 5; 

    if(id==0) sleep(1); 
    // if(id!=0) wait(); 

    printf("current process id: %d | parent preocess id:%d \n", getpid(), getppid()); 
    for (int i=num; i<num + 5; i++){
        printf("%d ", i); 
        fflush(stdout); 
    }
    printf("\n");

    int res= wait(NULL); 
    if (res==-1) printf("No children to wait for\n");
    else printf("%d finish execution\n", res); 

    return 0; 
}

// if parent get terminated before the child the parent of the child in zombie process