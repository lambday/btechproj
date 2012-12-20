#include <stdio.h>
#include <stdlib.h>
#include "include/spga.h"

int main( int argc, char* argv[] ) {
    //printf("Hello world!\n");
//    if( argc != 2 ) {
//        printf( "Format <input file name>" );
//        exit( EXIT_SUCCESS );
//    }
    //parseParam( argc, argv );
    //readGraph( argv[1] );
    char *ip = "P:\\Codes\\ShortestPathGA\\ShortestPathGA\\bin\\Debug\\input.graph";
    readGraph( ip );
//    _Bool PathNotFound = false;
//    populateList(); //0 for GreedyPopulation GPop
    GPop();
//    while( PathNotFound ) {
    int i;
    for( i = 0; i < GENERATIONS; ++i ) {
        //printf("i = %d\n", i );
        crossOver();
    }
//        mulation();
//        PathNotFound = examine();
//    }
    printShortestPath();
    return 0;
}
