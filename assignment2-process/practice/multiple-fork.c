#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
	int id1 = fork();
    int id2 = fork(); 

	if(id1==0) 
        if (id2==0)
		    printf("You are in super child\n");
        else
		    printf("You are in child\n");
	else if (id1 == -1 || id2 == -1)
		printf("Error occur at the time of creation\n");
	else
        if (id2==0) 
            printf("You are in another child of parent\n");
        else 
            printf("You are in parent\n"); 
    
    while(wait(NULL) != -1 || errno != ECHILD){
        printf("waiting for child to finish"); 
    }
}
