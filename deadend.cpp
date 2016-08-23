#include <iostream>
using namespace std;
#include <cmath>

#include "Maze.h"


int two2one(int i, int j, const int nMapWidth)
{
    return i * nMapWidth + j;
}

bool worth_checking(const int X1, const int Y1,
                    const int X2, const int Y2,
                    unsigned char* pMap, int i, int j, const int nMapWidth)
{
    if (pMap[two2one(i, j, nMapWidth)] == '0') {return false;}
    if (i == Y1 && j == X1) {return false;}
    if (i == Y2 && j == X2) {return false;}
    return true;
}

void deadend(const int X1, const int Y1,
             const int X2, const int Y2,
             unsigned char* pMap,
             const int nMapWidth, const int nMapHeight)
{
    int i, j;
    int count;

    /* Check corners */

    i = 0;
    j = 0;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
        count = 0;
        if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
        if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j, nMapWidth)] = '0';
        }
    }

    j = nMapWidth - 1;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
        count = 0;
        if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
        if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j, nMapWidth)] = '0';
        }
    }

    i = nMapHeight - 1;
    j = 0;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
        count = 0;
        if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
        if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j, nMapWidth)] = '0';
        }
    }

    j = nMapWidth - 1;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
        count = 0;
        if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
        if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
        if (count >= 1) {
            pMap[two2one(i, j, nMapWidth)] = '0';
        }
    }

    /* Check borders */

    i = 0;
    for (j=1; j<nMapWidth-1; j++) {
        if (worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
            count = 0;
            if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j, nMapWidth)] = '0';
            }
        }
    }

    i = nMapHeight-1;
    for (j=1; j<nMapWidth-1; j++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
            count = 0;
            if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j, nMapWidth)] = '0';
            }
        }
    }

    j = 0;
    for (i=1; i<nMapHeight-1; i++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
            count = 0;
            if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j, nMapWidth)] = '0';
            }
        }
    }

    j = nMapWidth-1;
    for (i=1; i<nMapHeight-1; i++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
            count = 0;
            if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
            if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
            if (count >= 2) {
                pMap[two2one(i, j, nMapWidth)] = '0';
            }
        }
    }

    /* Check interior */

    bool deadend_exists = true;
    while (deadend_exists) {
        deadend_exists = false;
        for (i=1; i<nMapHeight-1; i++) {
            for (j=1; j<nMapWidth-1; j++) {
                if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j, nMapWidth)) {
                    continue;
                }
                count = 0;
                if (pMap[two2one(i, j-1, nMapWidth)] == '0') {count++;}
                if (pMap[two2one(i, j+1, nMapWidth)] == '0') {count++;}
                if (pMap[two2one(i-1, j, nMapWidth)] == '0') {count++;}
                if (pMap[two2one(i+1, j, nMapWidth)] == '0') {count++;}
                if (count >= 3) {
                    /* There are 3 or more walls around this point, so it
                     * must be a dead end. Fill it in.
                     */
                    pMap[two2one(i, j, nMapWidth)] = '0';
                    deadend_exists = true;
                    /* If not a single deadend was found the iteration will
                     * stop.
                     */
                }
            }
        }
    }
}


void test(unsigned char* pMap)
{
    std::cout << "Test. Test. Test. \n";
    return;
}


int main(int argc, char* argv[]) {
    const int nx =  8;
    const int ny =  12;
    unsigned char maze[ny*nx] =
    {
        '0','0','0','0','0','0','0','0',
        '0','1','0','0','0','0','1','0',
        '0','1','1','0','1','1','1','0',
        '0','0','1','1','0','1','0','0',
        '0','0','0','1','1','1','0','0',
        '0','0','0','0','1','1','0','0',
        '0','1','0','0','0','1','1','0',
        '0','1','0','1','0','1','0','0',
        '0','1','1','1','1','1','1','0',
        '0','0','1','0','0','0','0','0',
        '0','1','1','1','1','1','1','0',
        '0','0','0','0','0','0','0','0'
    };

    int i, j;
    for (i=0; i<ny; i++) {
        for (j=0; j<nx; j++) {
            std::cout << maze[two2one(i, j, nx)] << " ";
        }
        std::cout << "\n";
    }

    // test(maze);
    deadend(1, 1, nx-2, ny-2, maze, nx, ny);

    std::cout << "Hello ParadoxPath. \n";

    for (i=0; i<ny; i++) {
        for (j=0; j<nx; j++) {
            std::cout << maze[two2one(i, j, nx)] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
