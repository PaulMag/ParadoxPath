#include <iostream>
using namespace std;
#include <cmath>
#include <vector>

#ifndef MAZE_H
#define MAZE_H

class Maze {

public:

    const int X1, Y1;
    const int X2, Y2;
    unsigned char* pMap;
    const unsigned char* pMapC;
    const int nX, nY;

    int currentBest;
    int* currentBestSnake;
    int nOutBufferSize;

    int* dir1, dir2;
    int** directions;

    Maze(const int, const int,
         const int, const int,
         unsigned char*, const int, const int);
    Maze(const int, const int,
         const int, const int,
         const unsigned char*, const int, const int);
    ~Maze();

    int two2one(int, int);
    int one2x(int);
    int one2y(int);

    int solve(int*, int);
    void forward(vector<int>, int);
    void setDirection(int);
    void setDirection(int, int);
    bool worth_checking(int, int);
    void deadend();
};

#endif
