#include <stdio.h>
#include <unistd.h>

int main(void) {
	int id = fork();

	if(id==0) 
		printf("You are in the child process\n");
	else if (id == -1)
		printf("Error occur at the time of creation\n");
	else
		printf("In the parent process\n"); 
}
