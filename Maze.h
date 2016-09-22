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

    int* snake;
    int currentBest;
    int* currentBestSnake;
    int nOutBufferSize;

    int* dir1, dir2;

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
    void forward(int);
    vector<vector<int>> setDirection(int);
    vector<vector<int>> setDirection(int, int);
    void deadend();
    void forward_d(int, int);
};

#endif
