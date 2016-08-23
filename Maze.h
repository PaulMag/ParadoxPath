#include <iostream>
using namespace std;
#include <cmath>

#ifndef MAZE_H
#define MAZE_H

class Maze {

public:

    const int X1, Y1;
    const int X2, Y2;
    const unsigned char* pMap;
    const int nX, nY;

    int currentBest;
    int* currentBestSnake;
    const int nOutBufferSize;

    int* dir1, dir2;
    int** directions;

    Maze(int, int, int, int, unsigned char*, int, int);
    ~Maze();

    int one2x(int);
    int one2y(int);

    int solve(int*, const int);
    void forward(int*, int);
    void setDirection();
};

#endif
