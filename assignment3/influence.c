//A3 program. Takes command "influence graph.txt T" and finds TOP1&2 influencers
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

struct qNode {
    int data;
    struct qNode* next;
    struct qNode* last;
};

struct Node {
    float data;
    int v;
    struct Node* next;
    struct Node* last;
    struct Node* previous;
    float distance;
    int state;
    int spread;
    int influenced;
};

typedef struct Node Node;
// Two glboal variables to store address of front and rear nodes.
struct qNode* front = NULL;
struct qNode* rear = NULL;

// To Enqueue an integer

void Enqueue(int x) {
    struct qNode* temp =
            (struct qNode*) malloc(sizeof (struct qNode));
    temp->data = x;
    temp->next = NULL;
    if (front == NULL) {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
    return;
}

// To Dequeue an integer.

int Dequeue() {
    struct qNode* temp = front;
    int value;
    if (front == NULL) {
        printf("Queue is Empty\n");
        return;
    }
    if (front == rear) {
        value = front->data;
        front = rear = NULL;
    } else {
        value = front->data;
        front = front->next;
    }
    free(temp);
    return value;
}

void addEdge(Node* index, int b, float w) {
    Node* temp = (Node*) malloc(sizeof (Node));

    if (index->last == NULL) {
        index->last = index;
        index->next = NULL;
        index->data = w;
        index->v = b;
        return;
    }

    index->last->next = temp;
    index->last = temp;
    temp->data = w;
    temp->v = b;
    return;
}

void printList(Node* index) {
    while (index != NULL) {
        printf(" %d-%f |", index->v, index->data);
        index = index->next;
    }
    return;
}

void Print() {
    struct qNode* temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void findSpread(int source, int nodes, float deadline, Node** vertex, int inf) {
    int i;
    int current;
    Node* temp;
    float estDist;

    for (i = 0; i < nodes; i++) {
        vertex[i]->distance = 2147483647 - 1; //Simulate infinity
        vertex[i]->state = 0;
        vertex[i]->previous = NULL;
        if (inf == 1)
            vertex[i]->spread = 0;
        if (inf == 0)
            vertex[i]->influenced = 0;
    }
    vertex[source]->distance = 0;
    if (front != NULL) {
        perror("Queue not Empty!!");
        return;
    }

    Enqueue(source);

    while (front != NULL) {
        current = Dequeue();
        if (vertex[current]->last != NULL)
            temp = vertex[current];
        else {
            temp = NULL;
        } //This is last node, move on
        while (temp != NULL) {
            estDist = vertex[current]->distance + temp->data;
            if (vertex[temp->v]->distance > estDist) {//Look at connected Node's
                //distance to source, relax
                vertex[temp->v]->distance = estDist;
            }
            if (vertex[temp->v]->state != 1) {
                vertex[temp->v]->state = 1;
                Enqueue(temp->v);
            }
            temp = temp->next;
        }
    }

    for (i = 0; i < nodes; i++) {
        if (vertex[i]->distance <= deadline) {
            if (inf == 0 || (inf == 2 && vertex[i]->influenced != 1))
                vertex[source]->spread++;
            if (inf == 1)
                vertex[i]->influenced = 1;
        }
    }
}

void findMaxSpread(Node** vertex, int nodes, int *topone, int *spreaderino) {
    int max = 0;
    int node = 0;
    int i;
    int counter = 0;
    int random = 0;

    for (i = 0; i < nodes; i++) {
        if (vertex[i]->spread > max) {
            counter = 1;
            max = vertex[i]->spread;
            node = i;
        } else if (vertex[i]->spread == max) {
            counter++; //Randomly breaks tie. This method does not need to
            //store all values to break at the end, ask me for proof of the
            //probabilistic outcomes
            random = rand() % 100;
            if (random < (100 / counter)) {
                max = vertex[i]->spread;
                node = i;
            }
        }
    }

    *topone = node;
    *spreaderino = vertex[node]->spread;

    return;

}

int main(int argc, char** argv) {
    /* Drive code to test the implementation. */
    // Printing elements in Queue after each Enqueue or Dequeue
    FILE *datafile;
    char str[50];
    char userInput[50];
    int i;
    int results[4] = {0, 0, 0, 0};
    int a, b, max;
    float deadline;
    Node** vertex;
    float w;
    max = 0;
    srand(time(NULL));
    double timeE1,timeE2;
    static struct timeval tv1, tv2;

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

    vertex = (Node **) malloc(sizeof (Node*)*(max + 1));
    for (i = 0; i < max + 1; i++) {
        vertex[i] = (Node *) malloc(sizeof (Node));
        vertex[i]->last = NULL;
        vertex[i]->next = NULL;
        vertex[i]->previous = NULL;
        vertex[i]->spread = 0;
    }

    datafile = fopen(argv[1], "r");
    while (fgets(str, 50, datafile) != NULL) {
        sscanf(str, "%d %d %f", &a, &b, &w);
        addEdge(vertex[a], b, w);
    }

    sscanf(argv[2], "%f", &deadline);

    gettimeofday(&tv1, NULL);
    for (i = 0; i < max + 1; i++) {
        findSpread(i, (max + 1), deadline, vertex, 0);
    }

    findMaxSpread(vertex, (max + 1), results, results + 1);

    gettimeofday(&tv2, NULL);
    
    timeE1 = ((tv2.tv_sec - tv1.tv_sec)*1000000L
           +tv2.tv_usec) - tv1.tv_usec;
    
    gettimeofday(&tv1, NULL);
    
    findSpread(results[0], (max + 1), deadline, vertex, 1);
    vertex[results[0]]->spread = 0;

    for (i = 0; i < max + 1; i++) {
        findSpread(i, (max + 1), deadline, vertex, 2);
    }

    findMaxSpread(vertex, (max + 1), results + 2, results + 3);

    gettimeofday(&tv2, NULL);
    
    timeE2 = ((tv2.tv_sec - tv1.tv_sec)*1000000L
           +tv2.tv_usec) - tv1.tv_usec;
    
    printf("TOP-1 INFLUENCER: %d, SPREAD: %d, TIME: %f usec\n", results[0], results[1], timeE1);
    printf("TOP-2 INFLUENCER: %d, MARGINAL SPREAD: %d, TIME: %f usec\n", results[2], results[3], timeE2);
    return (0);
}
