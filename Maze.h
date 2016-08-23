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
    int directions[4][2];

    Maze(const int, const int,
         const int, const int,
         unsigned char*, const int, const int);
    ~Maze();

    int two2one(int, int);
    int one2x(int);
    int one2y(int);

    int solve(int*, const int);
    void forward(int*, int);
    void setDirection();
    bool worth_checking(int, int);
    void deadend();
};

#endif
