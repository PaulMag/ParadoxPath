#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


Maze:: Maze(
    const int X1, const int Y1,
    const int X2, const int Y2,
    unsigned char* pMap, const int nX, const int nY) :
    X1(X1), Y1(Y1), X2(X2), Y2(Y2), nX(nX), nY(nY)
{
    // this->X1 = X1;
    // this->Y1 = Y1;
    // this->X2 = X2;
    // this->Y2 = Y2;
    this->pMap = pMap;
    // this->nX = nX;
    // this->nY = nY;
    this->directions = {{}{}};
}


Maze:: ~Maze()


int Maze:: solve(int* pOutBuffer, const int nOutBufferSize) :
    nOutBufferSize(nOutBufferSize)
{
    this->currentBest = nOutBufferSize + 2;
    this->currentBestSnake[nOutBufferSize+1] = {};
    currentBestSnake[0] = two2one(X2, Y2)
    // this->nOutBufferSize = nOutBufferSize;

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


int Maze:: two2one(int i, int j)
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


bool Maze:: worth_checking(int i, int j)
{
    if (pMap[two2one(i, j)] == '0') {return false;}
    if (i == Y1 && j == X1) {return false;}
    if (i == Y2 && j == X2) {return false;}
    return true;
}


void Maze:: deadend()
{
    int i, j;
    int count;

    /* Check corners */

    i = 0;
    j = 0;
    if (worth_checking(i, j)) {
        count = 0;
        if (pMap[two2one(i, j+1)] == '0') {count++;}
        if (pMap[two2one(i+1, j)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j)] = '0';
        }
    }

    j = nX - 1;
    if (worth_checking(i, j)) {
        count = 0;
        if (pMap[two2one(i, j+1)] == '0') {count++;}
        if (pMap[two2one(i-1, j)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j)] = '0';
        }
    }

    i = nY - 1;
    j = 0;
    if (worth_checking(i, j)) {
        count = 0;
        if (pMap[two2one(i, j-1)] == '0') {count++;}
        if (pMap[two2one(i+1, j)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j)] = '0';
        }
    }

    j = nX - 1;
    if (worth_checking(i, j)) {
        count = 0;
        if (pMap[two2one(i, j-1)] == '0') {count++;}
        if (pMap[two2one(i-1, j)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j)] = '0';
        }
    }

    /* Check borders */

    i = 0;
    for (j=1; j<nX-1; j++) {
        if (worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j-1)] == '0') {count++;}
            if (pMap[two2one(i, j+1)] == '0') {count++;}
            if (pMap[two2one(i+1, j)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j)] = '0';
            }
        }
    }

    i = nY-1;
    for (j=1; j<nX-1; j++) {
        if (! worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j-1)] == '0') {count++;}
            if (pMap[two2one(i, j+1)] == '0') {count++;}
            if (pMap[two2one(i-1, j)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j)] = '0';
            }
        }
    }

    j = 0;
    for (i=1; i<nY-1; i++) {
        if (! worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j+1)] == '0') {count++;}
            if (pMap[two2one(i-1, j)] == '0') {count++;}
            if (pMap[two2one(i+1, j)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j)] = '0';
            }
        }
    }

    j = nX-1;
    for (i=1; i<nY-1; i++) {
        if (! worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j-1)] == '0') {count++;}
            if (pMap[two2one(i-1, j)] == '0') {count++;}
            if (pMap[two2one(i+1, j)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j)] = '0';
            }
        }
    }

    /* Check interior */

    bool deadend_exists = true;
    while (deadend_exists) {
        deadend_exists = false;
        for (i=1; i<nY-1; i++) {
            for (j=1; j<nX-1; j++) {
                if (! worth_checking(i, j)) {
                    continue;
                }
                count = 0;
                if (pMap[two2one(i, j-1)] == '0') {count++;}
                if (pMap[two2one(i, j+1)] == '0') {count++;}
                if (pMap[two2one(i-1, j)] == '0') {count++;}
                if (pMap[two2one(i+1, j)] == '0') {count++;}
                if (count >= 3) {
                    /* There are 3 or more walls around this point, so it
                     * must be a dead end. Fill it in.
                     */
                    pMap[two2one(i, j)] = '0';
                    deadend_exists = true;
                    /* If not a single deadend was found the iteration will
                     * stop.
                     */
                }
            }
        }
    }
}
