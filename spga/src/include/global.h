#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"

FILE *input;
Graph graph[SIZE][SIZE];
int MinWeight[SIZE];
PathList *pathList[SIZE-1];

#endif // GLOBAL_H_INCLUDED
