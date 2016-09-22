#include <iostream>
using namespace std;
#include <cmath>
#include <vector>

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


int Maze:: solve(int* pOutBuffer, int nOutBufferSize)
{
    this->currentBest = nOutBufferSize + 2;
    this->currentBestSnake = new int[nOutBufferSize+1];
    currentBestSnake[0] = two2one(Y1, X1);
    this->nOutBufferSize = nOutBufferSize;

    this->snake = new int[nOutBufferSize+1];
    snake[0] = two2one(Y1, X1);
    forward(1);

    if (currentBest > nOutBufferSize + 1) {
        return -1;
    }
    else {
        int p;
        for (p=0; p<currentBest-1; p++) {
            // Do not count start position.
            pOutBuffer[p] = currentBestSnake[p+1];
        }
        return currentBest-1;
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


void Maze:: forward(int snakeSize)
{
    int p;
    for (p=0; p<snakeSize-1; p++) {
        if (snake[snakeSize-1] == snake[p]) {
            // Been here before.
            // cout << "been here before (" << snake[snakeSize-1] << ") \n";
            return;
        }
    }
    int bestPossibility = snakeSize +
                          abs(X2 - one2x(snake[snakeSize-1])) +
                          abs(Y2 - one2y(snake[snakeSize-1]));
    if (bestPossibility >= currentBest) {
        // A better solution cannot be found anymore.
        // cout << "A better solution cannot be found anymore. \n";
        return;
    }
    else if (bestPossibility > nOutBufferSize) {
        // Potential solution is too long.
        // cout << "Potential solution is too long. \n";
        return;
    }
    else if (snake[snakeSize-1] == two2one(Y2, X2)) {
        // Victory!
        // cout << "Victory! \n";
        currentBest = snakeSize;
        for (p=0; p<snakeSize; p++) {
            currentBestSnake[p] = snake[p];
        }
        return;
    }

    vector<vector<int>> directions = setDirection(currentBestSnake[0]);
    int e;
    int newpos[2] = {};
    for (e=0; e<4; e++)
    {
        newpos[0] = one2y(snake[snakeSize-1]) + directions[e][0];
        newpos[1] = one2x(snake[snakeSize-1]) + directions[e][1];
        if (newpos[0] < 0 or newpos[1] < 0 or newpos[0] >= nY or newpos[1] >= nX)
        {
            continue;  // out of bounds, skip forward
        }
        if (pMap[two2one(newpos[0], newpos[1])] == 1)  // if open path
        {
            snake[snakeSize] = two2one(newpos[0], newpos[1]);  // new head
            forward(snakeSize+1);  // continue moving
        }
        // elseif no open path: return
    }
    directions.clear();
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
