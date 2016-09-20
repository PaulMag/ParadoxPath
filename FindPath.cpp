#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
    Maze m = Maze(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight);
    m.deadend();
    return m.solve(pOutBuffer, nOutBufferSize);
}
