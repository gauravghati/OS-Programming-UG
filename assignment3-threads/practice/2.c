# include <stdio.h>
# include<stdlib.h>
# include<pthread.h>
# include <string.h>

#define MAX 50

/*

1) Printing Table  of a number : Pass number as a argument . Return Computed Table as a return value and print in main.

2) Reverse of the string: Pass string as a argument: Perform Reverse logic in Thread function and return reversed string as a return value and print in main

3) String Comparison: Pass both the strings to be compared as an argument, perform comparison in thread function and then return result of comparison to main

4) Element by Element Addition of two arrays using thread Function and return array Sum to main and print inside main

*/


char *reverses(void *params);

int main() {
	int res;
	char *p;
	
	pthread_t t_table; 
	char *tres;
	
	printf("\nWith main function");
	
	printf("\nEnter the string : ");
	scanf("%s", p); 
	
	res = pthread_create(&t_table, NULL, reverses, (void*)p);

	res = pthread_join(t_table, &tres);
	
	printf("%s\n", (char*)(tres));
		
	return 0; 
}

char *reverses(void *params) {
	
	char *p = (char *)params;
	int n = strlen(p);
	
	for (int i=0; i<n/2; i++) {
		char temp = p[i];
		p[i] = p[n-i-1];
		p[n-i-1] = temp;
	}
	
	pthread_exit(p);
}

