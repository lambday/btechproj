#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#define SIZE 20
#define GENERATIONS 20
#define source 0
#define dest 19

//typedef enum {
//    GreedyPopulation,
//    RandomPopulation
//} populateHeuristic;

//typedef struct {
//    char *FileName;
//    populateHeuristic Algo;
//} paramList;

typedef struct {
    int weight;
    //long long unsigned flag;
    unsigned int flag;
} Graph;

typedef struct node {
    int value;
    struct node* next;
} PathList;

#endif // TYPES_H_INCLUDED
