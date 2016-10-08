#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
#include <algorithm>


#include "Maze.h"


Maze:: Maze(
    const int X1, const int Y1,
    const int X2, const int Y2,
    unsigned char* pMap, const int nX, const int nY) :
    X1(X1), Y1(Y1), X2(X2), Y2(Y2), nX(nX), nY(nY)
{
    this->pMap = pMap;
}


Maze:: Maze(
    const int X1, const int Y1,
    const int X2, const int Y2,
    const unsigned char* pMapC, const int nX, const int nY) :
    X1(X1), Y1(Y1), X2(X2), Y2(Y2), nX(nX), nY(nY)
{
    this->pMap = new unsigned char[nX*nY];
    for (int k=0; k<nX*nY; k++)
    {
        pMap[k] = pMapC[k];
    }
}


Maze:: ~Maze() {}


void Maze:: initializeScores()
{
    previousMap = new int[nY*nX];
    hScores = new int[nY*nX];
    gScores = new int[nY*nX];
    fScores = new int[nY*nX];
    gScores[0] = nY*nX;

    for (int i=0; i<nY; i++) {
        for (int j=0; j<nX; j++) {
            hScores[i*nX+j] = abs(Y2 - i) + abs(X2 - j);
            gScores[i*nX+j] = gScores[0];
            fScores[i*nX+j] = gScores[0] + hScores[i*nX+j];
        }
    }

    priority.push_back(two2one(Y1, X1));
    priorityN = 1;
    gScores[priority[0]] = 0;
    fScores[priority[0]] = hScores[priority[0]];
    priorityF.push_back(fScores[priority[0]]);

    priority_temp.reserve(nY*nX/2);
    priorityF_temp.reserve(nY*nX/2);
}


int Maze:: solve(int* pOutBuffer, int nOutBufferSize)
{
    this->currentBest = nOutBufferSize + 1;
    this->nOutBufferSize = nOutBufferSize;
    initializeScores();
    this->directions = setDirection(Y1, X1);

    while (priorityN > 0) {
        explodeFirst();
        vector<int> idx = sort(priorityF);
        for (int p=0; p<priorityN; p++) {
            priority_temp[p]  = priority[p];
            priorityF_temp[p] = priorityF[p];
        }
        for (int p=0; p<priorityN; p++) {
            priority[p]  = priority_temp[idx[p]];
            priorityF[p] = priorityF_temp[idx[p]];
        }
        if (priorityF[0] >= currentBest or priorityF[0] > nOutBufferSize) {
            break;  // No better solution can exist anymore.
        }
    }

    if (currentBest > nOutBufferSize) {
        return -1;
    }
    else {
        pOutBuffer[currentBest-1] = two2one(Y2, X2);
        for (int p=currentBest-1; p>0; p--) {
            pOutBuffer[p-1] = previousMap[pOutBuffer[p]];
        }
        return currentBest;
    }
}


int Maze:: two2one(int y, int x)
{
    return y * nX + x;
}

int Maze:: one2x(int k)
{
    return k % nX;
}

int Maze:: one2y(int k)
{
    return k / nX;
}


vector<int> Maze:: sort(vector<int> data)
{
    std::vector<int> idx(data.size());
    std::size_t n(0);
    std::generate(std::begin(idx), std::end(idx), [&]{ return n++; });

    std::sort(  std::begin(idx),
                std::end(idx),
                [&](int i1, int i2) { return data[i1] < data[i2]; } );
    return idx;
}


void Maze:: explodeFirst()
{
    int pos = priority[0];
    priority.erase(priority.begin());
    priorityF.erase(priorityF.begin());
    priorityN--;

    if (pos == two2one(Y2, X2)) {
        // Victory!
        currentBest = gScores[pos];
        return;  // No need to explode from goal.
    }

    int newpos[2] = {};
    for (int e=0; e<4; e++)
    {
        newpos[0] = one2y(pos) + directions[e][0];
        newpos[1] = one2x(pos) + directions[e][1];
        if (newpos[0] < 0 or newpos[1] < 0 or newpos[0] >= nY or newpos[1] >= nX)
        {
            continue;  // out of bounds
        }
        else if (pMap[two2one(newpos[0], newpos[1])] == 0)
        {
            continue;  // closed path
        }
        else if (gScores[two2one(newpos[0], newpos[1])] > gScores[pos]+1) {
            priority.push_back(two2one(newpos[0], newpos[1]));
            previousMap[priority[priorityN]] = pos;
            gScores[priority[priorityN]] = gScores[pos] + 1;
            fScores[priority[priorityN]] = gScores[priority[priorityN]] + hScores[priority[priorityN]];
            priorityF.push_back(fScores[priority[priorityN]]);
            priorityN++;
        }
        // else: Better path already found to this location.
    }

    return;
}


vector<vector<int>> Maze:: setDirection(int headK)
{
    return setDirection(one2x(headK), one2y(headK));
}

vector<vector<int>> Maze:: setDirection(int headX, int headY)
{
    int dir[2] = {};
    dir[0] = X2 - headX;
    dir[1] = Y2 - headY;
    int i = 0;
    int j = 1;
    if (abs(dir[0]) < abs(dir[1]))
    {
        i = 1;
        j = 0;
    }
    vector<vector<int>> directions {{0,0}, {0,0}, {0,0}, {0,0}};

    if (dir[i] >= 0)
    {
        directions[0][i] = + (+1);
        directions[1][i] = + ( 0);
        directions[2][i] = + ( 0);
        directions[3][i] = + (-1);
    }
    else
    {
        directions[0][i] = - (+1);
        directions[1][i] = - ( 0);
        directions[2][i] = - ( 0);
        directions[3][i] = - (-1);
    }
    if (dir[j] >= 0)
    {
        directions[0][j] = + ( 0);
        directions[1][j] = + (+1);
        directions[2][j] = + (-1);
        directions[3][j] = + ( 0);
    }
    else
    {
        directions[0][j] = - ( 0);
        directions[1][j] = - (+0);
        directions[2][j] = - (-1);
        directions[3][j] = - ( 0);
    }
    return directions;
}


void Maze:: deadend()
{
    int i, j;
    for (i=0; i<nY; i++) {
        for (j=0; j<nX; j++) {
            if (pMap[two2one(i, j)] == 1) {  // Check if every open path
                forward_d(i, j);             // is a deadend.
            }
        }
    }
}


void Maze:: forward_d(int i, int j)
{
    int count = 0;
    int newpos[2] = {};

    if (j == 0) {count++;}  // edge
    else if (pMap[two2one(i, j-1)] == 0) {count++;}  // wall
    else {
        newpos[0] = i;    // open path
        newpos[1] = j-1;
    }

    if (j == nX-1) {count++;}
    else if (pMap[two2one(i, j+1)] == 0) {count++;}
    else {
        newpos[0] = i;
        newpos[1] = j+1;
    }

    if (i == 0) {count++;}
    else if (pMap[two2one(i-1, j)] == 0) {count++;}
    else {
        newpos[0] = i-1;
        newpos[1] = j;
    }

    if (i == nY-1) {count++;}
    else if (pMap[two2one(i+1, j)] == 0) {count++;}
    else {
        newpos[0] = i+1;
        newpos[1] = j;
    }

    if (count >= 3) {  // At least 3 walls or edges => deadend
        if (i == Y1 && j == X1) {return;}  // But not if it is the start
        if (i == Y2 && j == X2) {return;}  // or goal.
        pMap[two2one(i, j)] = 0;  // Close this deadend.
        if (count == 3) {       // If there was an open path
            forward_d(newpos[0], newpos[1]);  // check if that is also a deadend.
        }
    }
}
