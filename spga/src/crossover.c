#include "include/spga.h"

void crossOver() {
    //printf( "Crossover called\n" );

    /// Finding the fittest
    int fittest = 0, i;
    for( i = 1; i < SIZE-1; ++i ) {
        if( pathList[i]->value < pathList[fittest]->value )
            fittest = i;
    }

    int firstParent = fittest;
    int secondParent;
    do{
        secondParent = rand() % (SIZE-1);
    } while( secondParent == firstParent );
    /**
    printf( "firstParent is %d\n", firstParent );
    printf( "secondParent is %d\n", secondParent );
    **/
    PathList *firstPoint = pathList[firstParent]->next;
    PathList *secondPoint = pathList[secondParent]->next;
    /**
    printf( "Before crossover\n" );
    while( firstPoint != NULL ) {
        printf( "%d ", firstPoint->value );
        firstPoint = firstPoint->next;
    }
    printf( "\nweight = %d\n", pathList[firstParent]->value );
    while( secondPoint != NULL ) {
        printf( "%d ", secondPoint->value );
        secondPoint = secondPoint->next;
    }
    printf( "\nweight = %d\n", pathList[secondParent]->value );

    firstPoint = pathList[firstParent]->next;
    secondPoint = pathList[secondParent]->next;
    **/
    /// Skipping the initial part that's same
    while( firstPoint != NULL && secondPoint != NULL && firstPoint->value == secondPoint->value ) {
        firstPoint = firstPoint->next;
        secondPoint = secondPoint->next;
    }
    //printf( "found difference\n" );

    /// Finding the potential crossing sites
    PathList *temp, *temp2;
    int potentialSites[SIZE];
    int numberOfSites = 0;

    while( firstPoint != NULL ) {
        temp = secondPoint;
        /// If a point is commonly included in both chromosomes
        while( temp != NULL && firstPoint->value != temp->value ) {
            temp = temp->next;
        }
        if( temp != NULL ) {
//            printf( "Crossover point found at %d\n", temp->value );
            //secondPoint = temp;
            //break;
            /// Construct a set of potential crossing sites
            potentialSites[numberOfSites] = temp->value;
            //if( temp->next != NULL || firstPoint->next != NULL )
            numberOfSites++;
        }
        //
        firstPoint = firstPoint->next;
    }

    if( !numberOfSites )
        return;

    /// Randomly choose a crossing site
    int crossingSite = rand() % numberOfSites;
    /**
    printf( "\nCrossing site is %d (%d)\n", potentialSites[crossingSite], numberOfSites );
    **/
    /// Crossing over
    PathList *firstOffspring;
    PathList *secondOffspring;
    int x, y;

    /// Copying the first chromosome into a new child upto the crossing point
    firstPoint = pathList[firstParent]->next;
    int firstWeight = graph[source][firstPoint->value].weight;

    firstOffspring = malloc( sizeof(PathList) );
    firstOffspring->value = firstPoint->value;
    firstOffspring->next = NULL;
    temp = firstOffspring;
    if( temp->value != potentialSites[crossingSite] ) {
        firstPoint = firstPoint->next;
        while( firstPoint->value != potentialSites[crossingSite] ) {
            x = temp->value;
            y = firstPoint->value;
            temp->next = malloc( sizeof(PathList) );
            temp = temp->next;
            temp->value = firstPoint->value;
            temp->next = NULL;
            firstWeight += graph[x][y].weight;
            firstPoint = firstPoint->next;
        }
    }

    /// Copying the first chromosome into a new child upto the crossing point
    secondPoint = pathList[secondParent]->next;
    int secondWeight = graph[source][secondPoint->value].weight;

    secondOffspring = malloc( sizeof(PathList) );
    secondOffspring->value = secondPoint->value;
    secondOffspring->next = NULL;
    temp2 = secondOffspring;
    if( temp2->value != potentialSites[crossingSite] ) {
        secondPoint = secondPoint->next;
        while( secondPoint->value != potentialSites[crossingSite] ) {
            x = temp2->value;
            y = secondPoint->value;
            temp2->next = malloc( sizeof(PathList) );
            temp2 = temp2->next;
            temp2->value = secondPoint->value;
            temp2->next = NULL;
            secondWeight += graph[x][y].weight;
            secondPoint = secondPoint->next;
        }
    }

    /// Copying the rest of 2nd chromosome to 1st offspring
    while( firstPoint ) {
        x = temp2->value;
        y = firstPoint->value;
        temp2->next = malloc( sizeof(PathList) );
        temp2 = temp2->next;
        temp2->value = firstPoint->value;
        temp2->next = NULL;
        secondWeight += graph[x][y].weight;
        firstPoint = firstPoint->next;
    }
    secondWeight += graph[y][dest].weight;

    /// Copying the rest of 1st chromosome to 2nd offspring
    while( secondPoint ) {
        x = temp->value;
        y = secondPoint->value;
        temp->next = malloc( sizeof(PathList) );
        temp = temp->next;
        temp->value = secondPoint->value;
        temp->next = NULL;
        firstWeight += graph[x][y].weight;
        secondPoint = secondPoint->next;
    }
    firstWeight += graph[y][dest].weight;
//    temp = firstPoint->next;
//    firstPoint->next = secondPoint->next;
//    secondPoint->next = temp;
    /**
    printf( "\nAfter crossover\n" );
    //firstPoint = pathList[firstParent]->next;
    //secondPoint = pathList[secondParent]->next;
    temp = firstOffspring;

    while( temp != NULL ) {
        printf( "%d ", temp->value );
        temp = temp->next;
    }
    printf( "\nweight = %d\n", firstWeight );

    temp = secondOffspring;
    while( temp != NULL ) {
        printf( "%d ", temp->value );
        temp = temp->next;
    }
    printf( "\nweight = %d\n", secondWeight );
    **/

    /// Determining the fittest offspring and replacement
    if( firstWeight != pathList[firstParent]->value ) {
        if( firstWeight < secondWeight ) {
            if( firstWeight < pathList[secondParent]->value ) {
                pathList[secondParent]->value = firstWeight;
                pathList[secondParent]->next = firstOffspring;
            }
            if( secondWeight < pathList[firstParent]->value ) {
                pathList[firstParent]->value = secondWeight;
                pathList[firstParent]->next = secondOffspring;
            }
        } else {
            if( secondWeight < pathList[secondParent]->value ) {
                pathList[secondParent]->value = secondWeight;
                pathList[secondParent]->next = secondOffspring;
            }
            if( firstWeight < pathList[firstParent]->value ) {
                pathList[firstParent]->value = firstWeight;
                pathList[firstParent]->next = firstOffspring;
            }
        }
    }
    /**
    printf( "\nAfter a generation\n" );

    firstPoint = pathList[firstParent]->next;
    secondPoint = pathList[secondParent]->next;

    while( firstPoint != NULL ) {
        printf( "%d ", firstPoint->value );
        firstPoint = firstPoint->next;
    }
    printf( "\nweight = %d\n", pathList[firstParent]->value );
    while( secondPoint != NULL ) {
        printf( "%d ", secondPoint->value );
        secondPoint = secondPoint->next;
    }
    printf( "\nweight = %d\n", pathList[secondParent]->value );
    **/
}
