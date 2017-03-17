/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: wangjer1
 *
 * Created on March 16, 2017, 5:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 
 */

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
    int dens, i, j;

    FILE *fp = fopen("graph.txt", "w");
    if (fp == NULL) {
        perror("error file");
        exit(1);
    }

    fgets(userInput, sizeof (userInput), stdin);
    sscanf(userInput, "%d", &dens);

    for (i = 0; i < 100; i++) {
        //if (i % 2 == 0) {
            for (j = 0; j < dens + 1; j++) {
                if ((i + j + 1) > 99)
                    fprintf(fp, "%d %d %f\n", i, (i + j + 1 - 99), (float) (1 / (float) rand_lim()));
                else
                    fprintf(fp, "%d %d %f\n", i, (i + j + 1), (float) (1 / (float) rand_lim()));
            }
        //} else {
            for (j = 0; j < dens; j++) {
                if ((i + j + 1) > 99)
                    fprintf(fp, "%d %d %f\n", i, (i + j + 1 - 99), (float) (1 / (float) rand_lim()));
                else
                    fprintf(fp, "%d %d %f\n", i, (i + j + 1), (float) (1 / (float) rand_lim()));
            }
        //} Uncomment the three comments here if want to add 0.5 density
    }
    fclose(fp);



    return (EXIT_SUCCESS);
}
