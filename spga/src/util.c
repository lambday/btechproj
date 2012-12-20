#include "include/spga.h"

//extern FILE *input;
// graph stores the cost matrix
//extern Graph graph[SIZE][SIZE];

void readGraph( char *fileName ) {
    input = fopen( fileName, "rb" );
    if( input == NULL ) {
        perror( "Input File does not exist" );
        exit( EXIT_FAILURE );
    }
    int i, j;
    int min;
    for( i = 0; i < SIZE; ++i ) {
        min = 0;
        fread( &graph[i][0].weight, sizeof(int), 1, input );
        graph[i][0].flag = 0x0;//ffffffff;//ffffffffLLU;
        for( j = 1; j < SIZE; ++j ) {
            fread( &graph[i][j].weight, sizeof(int), 1, input );
            graph[i][j].flag = 0x0;//ffffffffLLU;
            if( graph[i][min].weight > graph[i][j].weight )
                min = j;
        }
        MinWeight[i] = min;
//        printf( "min = %d\n", graph[i][MinWeight[i]].weight );
    }
}

void printShortestPath() {
    int fittest = 0, i;
    for( i = 1; i < SIZE-1; ++i ) {
        if( pathList[i]->value < pathList[fittest]->value )
            fittest = i;
    }
    printf( "The Shortest Path obtained by GA is\n" );
    printf( "%d ", source );
    PathList *fittestPath = pathList[fittest]->next;
    while( fittestPath != NULL ) {
        printf( "%d ", fittestPath->value );
        fittestPath = fittestPath->next;
    }
    printf( "%d ", dest );
}
