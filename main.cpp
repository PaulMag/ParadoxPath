#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


int two2one(int y, int x, int nMapWidth)
{
    return y * nMapWidth + x;
}


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
    Maze m = Maze(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight);

    int i, j;
    for (i=0; i<nMapHeight; i++) {
        for (j=0; j<nMapWidth; j++) {
            cout << pMap[two2one(i, j, nMapWidth)] << " ";
        }
        cout << "\n";
    }
    cout << "Removing dead ends. \n";

    m.deadend();

    for (i=0; i<nMapHeight; i++) {
        for (j=0; j<nMapWidth; j++) {
            cout << m.pMap[two2one(i, j, nMapWidth)] << " ";
        }
        cout << "\n";
    }

    return m.solve(pOutBuffer, nOutBufferSize);
}


int main(int argc, char* argv[]) {
    const int nx =  10;
    const int ny =  12;
    const unsigned char pMapC[ny*nx] =
    {
        1,1,0,0,0,0,0,0,0,1,
        0,1,0,0,0,0,1,0,0,1,
        0,1,1,0,1,1,1,0,0,1,
        0,0,1,1,0,1,0,0,0,0,
        0,0,0,1,1,1,0,0,0,0,
        0,0,0,0,0,1,0,0,0,0,
        0,1,0,0,0,1,1,1,1,1,
        0,1,0,1,0,1,0,0,0,1,
        0,1,1,1,1,1,1,0,0,1,
        0,0,1,0,0,0,0,0,0,0,
        0,1,1,1,1,1,1,1,0,0,
        0,1,1,1,1,1,1,0,0,0,
    };

    int nOutBufferSize = 100;
    int* pOutBuffer = new int[nOutBufferSize];
    int best = FindPath(0, 0, 6, 11, pMapC, nx, ny, pOutBuffer, nOutBufferSize);

    std::cout << "Best solution: " << best << " steps. \n";
    for (int k=0; k<best; k++)
    {
        cout << pOutBuffer[k] << " ";
        if (k % 20 == 19)
        {
            cout << "\n";
        }
    }
    cout << "\n";

    return 0;
}
