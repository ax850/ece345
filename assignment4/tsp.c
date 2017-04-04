#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<math.h>

int main(int argc, char** argv) {

    FILE *datafile;
    char str[50];
    int i, j, mask, prevNode;
    int a, b, max;
    int temp;
    float** dist;
    float** sp;
    int** successor;
    float w, length;
    max = 0;
    srand(time(NULL));
    double timeE1, timeE2;
    static struct timeval tv1, tv2;
    int* reverse;

    datafile = fopen(argv[1], "r");
    if (datafile == NULL) {
        perror("Error with file");
        return (-1);
    }

    while (fgets(str, 50, datafile) != NULL) {
        sscanf(str, "%d %d %f", &a, &b, &w);
        if (a > max)
            max = a;
        if (b > max)
            max = b;
    }

    fclose(datafile);

    reverse = (int*) malloc(sizeof (int)*(max + 1));

    dist = (float**) malloc(sizeof (float*)*(max + 1));
    for (i = 0; i < (max + 1); i++) {
        dist[i] = (float*) malloc(sizeof (float)*(max + 1));
    }

    for (i = 0; i < (max + 1); i++) {
        for (j = 0; j < (max + 1); j++) {
            dist[i][j] = 0;
        }
    }

    datafile = fopen(argv[1], "r");
    while (fgets(str, 50, datafile) != NULL) {
        sscanf(str, "%d %d %f", &a, &b, &w);
        dist[a][b] = w;
    }
    fclose(datafile);

    for (i = 0; i < (max + 1); i++) {
        for (j = 0; j < (max + 1); j++) {
            if (dist[i][j] == 0)
                dist[i][j] = dist[j][i];
        }
    }

    gettimeofday(&tv1, NULL);

    sp = (float**) malloc(sizeof (float*)*(max + 1));
    for (i = 0; i < (max + 1); i++) {
        sp[i] = (float*) malloc(sizeof (float)*((int) (1 << max)));
        for (j = 0; j < ((int) (1 << max)); j++) {
            sp[i][j] = INFINITY;
        }
    }

    successor = (int**) malloc(sizeof (int*)*(max + 1));
    for (i = 0; i < (max + 1); i++) {
        successor[i] = (int*) malloc(sizeof (int)*((int) (1 << max)));
        for (j = 0; j < ((int) (1 << max)); j++) {
            successor[i][j] = INFINITY;
        }
    }

    sp[1][1] = 0;
    for (mask = 1; mask < ((int) (1 << max)); mask++) {
        for (prevNode = 1; prevNode < (max + 1); prevNode++) {
            if ((int) (mask & (1 << (prevNode - 1))) == 0)
                continue;
            for (j = 1; j < (max + 1); j++) {
                if ((int) (mask & (1 << (j - 1))) != 0)
                    continue;
                temp = ((int) (mask | (1 << (j - 1))));
                if (sp[j][temp] > (sp[prevNode][mask] + dist[prevNode][j])) {
                    sp[j][temp] = sp[prevNode][mask] + dist[prevNode][j];
                    successor[j][temp] = prevNode;
                }
            }
        }
    }

    length = INFINITY;
    for (prevNode = 1; prevNode < (max + 1); prevNode++) {
        temp = (int) ((1 << max) - 1);
        if (length > (dist[prevNode][1] + sp[prevNode][temp])) {
            length = (dist[prevNode][1] + sp[prevNode][temp]);
            a = prevNode;
        }
    }

    mask = (1 << max) - 1;

    i = (max - 1);

    while (mask != 0) {
        reverse[i--] = a;
        temp = a;
        a = successor[a][mask];
        mask = mask^(1 << (temp - 1));
    }
    reverse[max] = 1;

    gettimeofday(&tv2, NULL);

    timeE2 = ((tv2.tv_sec - tv1.tv_sec)*1000000L
           +tv2.tv_usec - tv1.tv_usec);

    printf("OPTIMAL TOUR LENGTH: %f\n", length);
    printf("TSP TOUR:\n");

    for (i = 0; i < (max + 1); i++) {
        printf("%d\n", reverse[i]);
    }

    printf("Time elapsed: %f usecs\n", timeE2);

    return 0;
}

