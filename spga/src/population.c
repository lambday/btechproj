#include "include/spga.h"

int Queue[SIZE];
int front, rear;

void InitializeQ() {
    //printf( "New queue initialized\n" );
    front = 0;
    rear = 0;
}

void Enque( int val ) {
    Queue[rear] = val;
    rear++;
}

int Dequeue() {
    int val = Queue[front];
    front++;
    return val;
}

int isEmpty() {
    return ( front == rear );
}

void GPop() {
    //method code
    int i, j;
    for( i = 0; i < SIZE - 1; ) {
        //long long unsigned isTraversed = 0xffffffffffffffffLLU;
        unsigned int isTraversed = 0xffffffff;
        int isValid = 0;
        int currentNode = source;
        int nextNode;
        InitializeQ();
        int *isVisited; // for avoiding loops in paths
        isVisited = calloc( SIZE, sizeof(int) );
        isVisited[source] = 1;
        //printf( "NEW ATTEMP START\n" );
        for( j = 0; j < SIZE; ++j ) {
            // with probability p = 0.75
            if( rand() % RAND_MAX / (double) RAND_MAX <= 0.6 ) {
                nextNode = MinWeight[currentNode];
                //printf( "%d) selecting min, %d\n", j, nextNode );
            } else {
                do{
                    nextNode = rand() % 20;
                } while( graph[currentNode][nextNode].weight == 10000 );
                //printf( "%d) selecting randomly %d\n", j, nextNode );
            }
            // for avoiding loops
            if( isVisited[nextNode] ) {
                //printf( "%d) selected %d, but already visited\n", j, nextNode );
                do{
                    nextNode = rand() % 20;
                    if( isVisited[nextNode] )
                        ++j;
                } while( (graph[currentNode][nextNode].weight == 10000 || isVisited[nextNode]) && j < SIZE );
                //printf( "%d) selecting randomly for avoiding loops %d\n", j, nextNode );
            }
            if( j == SIZE )
                break;
            isVisited[nextNode] = 1;
            //printf( "%d) FINALLY SELECTED %d\n", j, nextNode );
            //printf( "Current Node %d, weight %d\n", nextNode, graph[currentNode][nextNode].weight );
            /// Check if this path has already been traversed or not
            if( isTraversed != 0x0 ) {
                //printf( "Previous isTraversed %x\n", isTraversed );
                isTraversed &= graph[currentNode][nextNode].flag;
                //printf( "New isTraversed %x\n", isTraversed );
                //printf( "i = %d, Fucked up in previous path\n", i );
            } else {
                //printf( "New probable path found\n" );
            }
            /// Check if we already have reached the destination or not
            if( nextNode == dest ) {
                isValid = 1;
                break;
                //printf( "Yippie! Reached destination\n" );
            }
            Enque( nextNode );
            currentNode = nextNode;
        }
        if( !isTraversed && isValid ) {
            int x = source, y;//, k = 1;
            //PathList[i][0] = source;
            pathList[i] = malloc( sizeof(PathList*));
            pathList[i]->next = NULL;
            PathList *ptr = pathList[i];
            int totalWeight = 0;
            //printf( "Path : %d\n", i );
            while( !isEmpty() ) {
                y = Dequeue();
                //printf( "Previous flag (%d,%d) is %x\n", x, y, graph[x][y].flag );
                //printf( "(%d,%d), ", x, y );
                graph[x][y].flag |= (0x1 << i);
                totalWeight += graph[x][y].weight;
                x = y;
                PathList *temp = malloc( sizeof(PathList*));
                temp->value = x;
                temp->next = NULL;
                //PathList[i][k] = x;
                ptr->next = temp;
                ptr = ptr->next;
                //++k;
            }
            totalWeight += graph[y][dest].weight;
            pathList[i]->value = totalWeight;
            //printf( "\n" );
            //printf( "Total weight = %d\n", totalWeight );
            //PathList[i][k] = -1;
            ++i;
        } else {
            //printf( "Path discarded\n" );
        }
        free( isVisited );
    }
//    for( i = 0; i < SIZE-1; ++i ){
//        printf( "\nPath (%d) Weight %d\n", i, pathList[i]->value );
//        PathList *ptr = pathList[i]->next;
//        while( ptr != NULL ) {
//            printf( "%d ", ptr->value );
//            ptr = ptr->next;
//        }
//    }
}
