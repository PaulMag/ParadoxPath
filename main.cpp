#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


int two2one(int y, int x, int nMapWidth)
{
    return y * nMapWidth + x;
}


void test(unsigned char* pMap)
{
    std::cout << "Test. Test. Test. \n";
    return;
}


int main(int argc, char* argv[]) {
    const int nx =  10;
    const int ny =  12;
    unsigned char maze[ny*nx] =
    {
        '0','0','0','0','0','0','0','0','0','0',
        '0','1','0','0','0','0','1','0','0','0',
        '0','1','1','0','1','1','1','0','0','0',
        '0','0','1','1','0','1','0','0','0','0',
        '0','0','0','1','1','1','0','0','0','0',
        '0','0','0','0','0','1','0','0','0','0',
        '0','1','0','0','0','1','1','0','0','0',
        '0','1','0','1','0','1','0','0','0','0',
        '0','1','1','1','1','1','1','0','0','0',
        '0','0','1','0','0','0','0','0','0','0',
        '0','1','1','1','1','1','1','0','0','0',
        '0','0','0','0','0','0','0','0','0','0'
    };

    int i, j;
    for (i=0; i<ny; i++) {
        for (j=0; j<nx; j++) {
            std::cout << maze[two2one(i, j, nx)] << " ";
        }
        std::cout << "\n";
    }

    // test(maze);
    // deadend(1, 1, nx-2, ny-2, maze, nx, ny);
    Maze m = Maze(1, 1, 6, 10, maze, nx, ny);

    std::cout << "Hello ParadoxPath. \n";

    m.deadend();

    for (i=0; i<ny; i++) {
        for (j=0; j<nx; j++) {
            std::cout << m.pMap[two2one(i, j, nx)] << " ";
        }
        std::cout << "\n";
    }

    int best;
    int pOutBufferSize = 100;
    int* pOutBuffer = new int[pOutBufferSize];
    best = m.solve(pOutBuffer, pOutBufferSize);

    std::cout << "Best solution: " << best << " steps. \n";
    for (int k=0; k<pOutBufferSize; k++)
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
