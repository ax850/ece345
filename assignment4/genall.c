#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<math.h>

int rand_lim() {

    int divisor = RAND_MAX / 100;
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval == 100 || retval == 0);

    return retval;
}

int main(int argc, char** argv) {

    srand(time(NULL));
    char userInput[10];
    int dens, i, j, k;
    char fileName[20];
    
    for(dens = 5; dens<=25; dens=dens+2){
    snprintf(fileName, 20, "numCities%d.txt", dens);
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        perror("error file");
        exit(1);
    }

	
	for(i = 1; i<(dens+1);i++){
		for(j=i+1;j<(dens+1);j++){
			fprintf(fp, "%d %d %d\n", i, j, rand_lim());
		}
	}
	fclose(fp);
}

    return (EXIT_SUCCESS);
}
