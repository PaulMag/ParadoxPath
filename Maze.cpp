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
    this->directions = new int*[4];
    for(int i=0; i<4; i++)
        directions[i] = new int[2];
}


Maze:: Maze(
    const int X1, const int Y1,
    const int X2, const int Y2,
    const unsigned char* pMapC, const int nX, const int nY) :
    X1(X1), Y1(Y1), X2(X2), Y2(Y2), nX(nX), nY(nY)
{
    this->directions = new int*[4];
    for(int i=0; i<4; i++)
        directions[i] = new int[2];

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

    setDirection(currentBestSnake[0]);
    vector<int> snake(nOutBufferSize+1);
    snake[0] = two2one(Y1, X1);
    forward(snake, 1);

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


void Maze:: forward(vector<int> snake, int snakeSize)
{
    // print np.array(snake).tolist()  // Print current snake.
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
        cout << "A better solution cannot be found anymore. \n";
        return;
    }
    else if (bestPossibility > nOutBufferSize) {
        // Potential solution is too long.
        cout << "Potential solution is too long. \n";
        return;
    }
    else if (snake[snakeSize-1] == two2one(Y2, X2)) {
        // Victory!
        cout << "Victory! \n";
        currentBest = snakeSize;
        for (p=0; p<snakeSize; p++) {
            currentBestSnake[p] = snake[p];
        }
        return;
    }

    int e;
    int newpos[2] = {};
    for (e=0; e<4; e++)
    {
        newpos[0] = one2y(snake[snakeSize-1]) + directions[e][0];
        newpos[1] = one2x(snake[snakeSize-1]) + directions[e][1];
        if (newpos[0] < 0 or newpos[1] < 0 or newpos[0] >= nY or newpos[1] >= nX)
        {
            return;  // out of bounds
        }
        if (pMap[two2one(newpos[0], newpos[1])] == '1')  // if open path
        {
            snake[snakeSize] = two2one(newpos[0], newpos[1]);  // new head
            forward(snake, snakeSize+1);  // continue moving
        }
        // elseif no open path: stop
    }
}


void Maze:: setDirection(int headK)
{
        setDirection(one2x(headK), one2y(headK));
}

void Maze:: setDirection(int headX, int headY)
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

    bool deadend_exists = true;
    while (deadend_exists) {
        deadend_exists = false;

        /* Check corners */

        i = 0;
        j = 0;
        if (worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j+1)] == '0') {count++;}
            if (pMap[two2one(i+1, j)] == '0') {count++;}
            if (count >= 1) {
                pMap[two2one(i, j)] = '0';
                deadend_exists = true;
            }
        }

        j = nX - 1;
        if (worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j-1)] == '0') {count++;}
            if (pMap[two2one(i+1, j)] == '0') {count++;}
            if (count >= 1) {
                pMap[two2one(i, j)] = '0';
                deadend_exists = true;
            }
        }

        i = nY - 1;
        j = 0;
        if (worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j+1)] == '0') {count++;}
            if (pMap[two2one(i-1, j)] == '0') {count++;}
            if (count >= 1) {
                pMap[two2one(i, j)] = '0';
                deadend_exists = true;
            }
        }

        j = nX - 1;
        if (worth_checking(i, j)) {
            count = 0;
            if (pMap[two2one(i, j-1)] == '0') {count++;}
            if (pMap[two2one(i-1, j)] == '0') {count++;}
            if (count >= 1) {
                pMap[two2one(i, j)] = '0';
                deadend_exists = true;
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
                    deadend_exists = true;
                }
            }
        }

        i = nY-1;
        for (j=1; j<nX-1; j++) {
            if (worth_checking(i, j)) {
                count = 0;
                if (pMap[two2one(i, j-1)] == '0') {count++;}
                if (pMap[two2one(i, j+1)] == '0') {count++;}
                if (pMap[two2one(i-1, j)] == '0') {count++;}
                if (count >= 2) {
                    pMap[two2one(i, j)] = '0';
                    deadend_exists = true;
                }
            }
        }

        j = 0;
        for (i=1; i<nY-1; i++) {
            if (worth_checking(i, j)) {
                count = 0;
                if (pMap[two2one(i, j+1)] == '0') {count++;}
                if (pMap[two2one(i-1, j)] == '0') {count++;}
                if (pMap[two2one(i+1, j)] == '0') {count++;}
                if (count >= 2) {
                    pMap[two2one(i, j)] = '0';
                    deadend_exists = true;
                }
            }
        }

        j = nX-1;
        for (i=1; i<nY-1; i++) {
            if (worth_checking(i, j)) {
                count = 0;
                if (pMap[two2one(i, j-1)] == '0') {count++;}
                if (pMap[two2one(i-1, j)] == '0') {count++;}
                if (pMap[two2one(i+1, j)] == '0') {count++;}
                if (count >= 2) {
                    pMap[two2one(i, j)] = '0';
                    deadend_exists = true;
                }
            }
        }

        /* Check interior */

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
