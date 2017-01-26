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

void Merge(int * primary_key_arr, int left, int mid, int right){
	int i, j;
    int n1 = mid - left + 1;
    int n2 =  right - mid;
    int Left_arr[n1], Right_arr[n2];
 
	/*Creating temporary array for matching purposes*/
    
    for (i = 0; i < n1; i++)						
        Left_arr[i] = primary_key_arr[left + i];
    for (j = 0; j < n2; j++)
        Right_arr[j] = primary_key_arr[mid + 1+ j];
 
  
    int left_index = 0;
    int right_index = 0; 
    int inital_merge_index = left; 
	
	/*Merging each subarray together*/
	
    while (left_index < n1 && right_index < n2)
    {
        if (Left_arr[left_index] <= Right_arr[right_index])
        {
			/*Add node from left_arr to final array*/
            primary_key_arr[inital_merge_index] = Left_arr[left_index];	
            left_index++;
        }
        else
        {
			/*Add node from right_arr to final array*/
            primary_key_arr[inital_merge_index] = Right_arr[right_index];
            right_index++;
        }
        inital_merge_index++;
    }
 
	/*In case of uneven subarrays, must fillout*/
	
    while (left_index < n1)
    {
        primary_key_arr[inital_merge_index] = Left_arr[left_index];
        left_index++;
        inital_merge_index++;
    }
 
    while (right_index < n2)
    {
        primary_key_arr[inital_merge_index] = Right_arr[right_index];
        right_index++;
        inital_merge_index++;
    }
}

void merge_sort(int * primary_key_arr,int left, int right){
	if( left < right){
		int mid  = (left + right)/2;
		merge_sort(primary_key_arr,left,mid);
		merge_sort(primary_key_arr,mid + 1,right);
		Merge(primary_key_arr,left,mid,right);
	}
	else{
		return;
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
	
	clock_t begin = clock();
	
	merge_sort(primary_key_arr, 0, i-1);
	clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n",time_spent);
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

/*void swap(int * primary_key_arr, int x, int y){
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
	
}*/