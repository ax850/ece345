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

void swap(int * primary_key_arr, int x, int y){
	int temp = primary_key_arr[x];
	primary_key_arr[x] = primary_key_arr[y];
	primary_key_arr[y] = temp;
	return;
}

int partition( int * primary_key_arr, int left, int right){
	int pivot = primary_key_arr[right];
	int left_p = left -1;
	int right_p = right;
	while(true){
		while(primary_key_arr[++left_p] < pivot){
			// keep incremeting left pointer
		}
		while(primary_key_arr[--right_p] > pivot){
			//keep decrementing right pointer
		}
		if(left_p >= right_p){
			break;	// Went through the whole array, time to stop
		}
		else{
			swap(primary_key_arr, left_p, right_p);	// Swap when the conditions are met
		}
		
	}
	swap(primary_key_arr,left_p, right);	// Left_p now contains the correct place for the pivot 
	return left_p;
}

void quick_sort(int * primary_key_arr, int left,int right){
	if ( left < right){
		
		int index = partition(primary_key_arr,left,right);
		quick_sort(primary_key_arr, left, index-1);
		quick_sort(primary_key_arr, index+1, right);
	}
	
}

int main(int argc, char **argv){
	FILE* stream = fopen(argv[1], "r");
	int *primary_key_arr;
	
	primary_key_arr = (int *)malloc(sizeof(int)*50);
	
	char line[1024];
	int i = 0;
	while (fgets(line, 1024, stream))
    {
		char *pt = strtok(line, ",");
		primary_key_arr[i] = atoi(pt);
		i++;
    }
	quick_sort(primary_key_arr, 0, i-1);
	
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
    }
	
	return 0;
}