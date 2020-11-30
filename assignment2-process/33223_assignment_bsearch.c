# include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int i, arr[20],res, search, x;
    printf("No of arguments passed : %d", argc);

    for(int i=0; i<argc; i++)
        printf("\nArg[%d] : %s", i, argv[i]);
    
    printf("\n\tARGC : %d", argc);
    
    for(i=1; i<argc; i++)
        arr[i-1] = atoi(argv[i]);
    
    search = arr[argc-2];
    printf("\nSearch : %d", search);
    
    res = binarySearch(arr, 0, argc-3, search);
    if(res==-1) printf("\n\tELEMENT NOT FOUND!\n");
    else printf("\n\tELEMENT FOUND AT POSITION %d.\n", res+1);
}