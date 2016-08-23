#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


Maze:: Maze(
    const int X1, const int Y1,
    const int X2, const int Y2,
    unsigned char* pMap, const int nX, const int nY)
{
    this->X1 = X1;
    this->Y1 = Y1;
    this->X2 = X2;
    this->Y2 = Y2;
    this->pMap = pMap;
    this->nX = nX;
    this->nY = nY;
    this->directions[4][2] = {{}{}};
}


Maze:: ~Maze()


int Maze:: solve(int* pOutBuffer, const int nOutBufferSize)
{
    this->currentBest = nOutBufferSize + 2;
    this->currentBestSnake[nOutBufferSize+1] = {};
    currentBestSnake[0] = two2one(X2, Y2)
    this->nOutBufferSize = nOutBufferSize;

    set_direction()
    forward(currentBestSnake, 1)

    if (currentBest > nOutBufferSize + 1) {
        return -1;
    }
    else {
        int p;
        for (p=0; p<currentBest-1; p++) {
            // Do not count start position.
            pOutBuffer[p] = currentBestSnake[p+1];
        }
        return currentBest;
    }
}


int two2one(int i, int j)
{
    return i * nX + j;
}

int Maze:: one2x(int k)
{
    return k % nX;
}


int Maze:: one2y(int k)
{
    return k / nX;
}


void Maze:: forward(int* snake, int snakeSize)
{
    // print np.array(snake).tolist()  // Print current snake.
    int p;
    for (p=0; p<snakeSize-1; p++) {
        if (snake[snakeSize-1] == snake[p]) {
            // Been here before.
            // print "Been here before: %s" % str(prevPos)
            return;
        }
    }
    int bestPossibility = snakeSize +
                          abs(X2 - one2x(snake[snakeSize-1])) +
                          abs(Y2 - one2y(snake[snakeSize-1]));
    if (bestPossibility >= self.currentBest) {
        // A better solution cannot be found anymore.
        // print "A better solution cannot be found anymore."
        return;
    }
    else if (bestPossibility > self.nOutBufferSize) {
        // Potential solution is too long.
        // print "Potential solution is too long."
        return;
    }
    else if (snake[snakeSize-1] == two2one(X2, Y2)) {
        // Victory!
        // print "Victory!"
        currentBest = snakeSize;
        for (p=0; p<snakeSize; p++) {
            currentBestSnake[p] = snake[p];
        }
        return;
    }

    // self.set_direction(snake[~0])
        // This changing "globally" all the time causes some paths to be
        // tried two times.
        // Should it even be used?
    int e;
    int newpos[2] = {};
    for (e=0; e<4; e++):
        newPos[0] = snake[snakeSize-1] + direction[e][0];
        newPos[1] = snake[snakeSize-1] + direction[e][1];
        if (pMap[two2one(newPos[0], newPos[1])] == 1):  // if open path
        {
            snake[snakeSize] = two2one(newpos[0], newpos[1]);  // new head
            forward(snake, snakeSize+1)  // continue moving
        }
}


void Maze:: setDirection()
{
        int dir[2] = {};
        int dir[0] = X2 - one2x(snake[snakeSize-1])
        int dir[1] = Y2 - one2y(snake[snakeSize-1])
        int i = 0;
        int j = 1;
        if (abs(dirX) < abs(dirY))
        {
            i = 1;
            j = 0;
        }

        if dir[d] >= 0:
            directions[0][i] = + (+1)
            directions[1][i] = + ( 0)
            directions[2][i] = + ( 0)
            directions[3][i] = + (-1)
        else:
            directions[0][i] = - (+1)
            directions[1][i] = - ( 0)
            directions[2][i] = - ( 0)
            directions[3][i] = - (-1)
        if dir[j] >= 0
            directions[0][j] = + ( 0)
            directions[1][j] = + (+1)
            directions[2][j] = + (-1)
            directions[3][j] = + ( 0)
        else:
            directions[0][j] = - ( 0)
            directions[1][j] = - (+0)
            directions[2][j] = - (-1)
            directions[3][j] = - ( 0)
}
