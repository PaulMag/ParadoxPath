#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
#include <algorithm>

#ifndef MAZE_H
#define MAZE_H

class Maze {

public:

    const int X1, Y1;
    const int X2, Y2;
    unsigned char* pMap;
    const unsigned char* pMapC;
    const int nX, nY;

    int* previousMap;
    int* hScores;
    int* gScores;
    int* fScores;
    vector<int> priority;
    vector<int> priority_temp;
    vector<int> priorityF;
    vector<int> priorityF_temp;
    int priorityN;

    int currentBest;
    int nOutBufferSize;
    vector<vector<int>> directions;

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

    void initializeScores();
    int solve(int*, int);
    vector<int> sort(vector<int>);
    void explodeFirst();
    vector<vector<int>> setDirection(int);
    vector<vector<int>> setDirection(int, int);
    void deadend();
    void forward_d(int, int);
};

#endif
