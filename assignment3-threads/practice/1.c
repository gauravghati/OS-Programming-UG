 # include<stdio.h>
# include<stdlib.h>
# include<pthread.h>

#define MAX 50

/*

1) Printing Table  of a number : Pass number as a argument . Return Computed Table as a return value and print in main.

2) Reverse of the string: Pass string as a argument: Perform Reverse logic in Thread function and return reversed string as a return value and print in main

3) String Comparison: Pass both the strings to be compared as an argument, perform comparison in thread function and then return result of comparison to main

4) Element by Element Addition of two arrays using thread Function and return array Sum to main and print inside main

*/


int *table(void *params);

int main() {
	int res;
	int *p;
	
	pthread_t t_table; 
	int *tres;
	
	printf("\nWith main function");
	
	printf("\nEnter the number : ");
	scanf("%d", p); 
	
	res = pthread_create(&t_table, NULL, table, (void*)p);

	res = pthread_join(t_table, &tres);
	
	for (int i=1; i<=10; i++)
		printf("%d * %d = %d\n", i, *p, tres[i-1]);
	
	return 0; 
}

int *table(void *params) {
	
	int p = *(int *)params;
	int *ans= (int *)malloc(sizeof(int)*10);
	
	for (int i=1; i<=10; i++)
		ans[i-1] = i*p;
	
	pthread_exit(ans); 
}

