#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void insertion_sort(int *primary_key_arr, int n){
	//printf("%d and size is %d",primary_key_arr[0],n);
	int i = 1;
	for (i; i < n; i++){
		int key = primary_key_arr[i];
		int j = i - 1; 
		while(j >= 0 && primary_key_arr[j] > key){
			primary_key_arr[j+1] = primary_key_arr[j];
			j = j-1;
		}
		primary_key_arr[j+1] = key;
	}
	
}

int main(int argc, char **argv){
	FILE* stream = fopen(argv[1], "r");
	int *primary_key_arr;
	
	primary_key_arr = (int *)malloc(sizeof(int)*10000);
	
	char line[1024];
	int i = 0;
	while (fgets(line, 1024, stream))
    {
		char *pt = strtok(line, ",");
		primary_key_arr[i] = atoi(pt);
		i++;
    }
	clock_t begin = clock();
	insertion_sort(primary_key_arr,i); // i is 10 and size of array is also 10 if we start counting from 1
	clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("%f\n",time_spent);
	
	
	char line_t[1024];
	int x = 0;
	while (x < i)
    {		
		FILE* stream1 = fopen(argv[1], "r");
		while(fgets(line_t, 1024, stream1)){
			char temp[1024];
			strcpy(temp,line_t);
			char *pt = strtok(line_t, ",");
			//printf("%s and primary_key = %d at index = %d\n",pt,primary_key_arr[x],x);
			if(primary_key_arr[x] == atoi(pt)){
				printf("%s\n",temp);
				break;
			}
		}
		x++;
		fclose(stream1);
    }
	free(primary_key_arr);
	return 0;
}