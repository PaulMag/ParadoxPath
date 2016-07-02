#include <iostream>
using namespace std;


bool worth_checking(const int X1, const int Y1,
                    const int X2, const int Y2,
                    unsigned char** pMap, int i, int j)
{
    if (pMap[i][j] == '0') {return false;}
    if (i == Y1 && j == X1) {return false;}
    if (i == Y2 && j == X2) {return false;}
    return true;
}

void deadend(const int X1, const int Y1,
             const int X2, const int Y2,
             unsigned char** pMap,
             const int nMapWidth, const int nMapHeight)
{
    int i, j;
    int count;

    /* Check corners */

    i = 0;
    j = 0;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
        count = 0;
        if (pMap[i][j+1] == '0') {count++;}
        if (pMap[i+1][j] == '0') {count++;}
        if (count >= 1) {
            pMap[i][j] = '0';
        }
    }

    j = nMapWidth - 1;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
        count = 0;
        if (pMap[i][j+1] == '0') {count++;}
        if (pMap[i-1][j] == '0') {count++;}
        if (count >= 1) {
            pMap[i][j] = '0';
        }
    }

    i = nMapHeight - 1;
    j = 0;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
        count = 0;
        if (pMap[i][j-1] == '0') {count++;}
        if (pMap[i+1][j] == '0') {count++;}
        if (count >= 1) {
            pMap[i][j] = '0';
        }
    }

    j = nMapWidth - 1;
    if (worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
        count = 0;
        if (pMap[i][j-1] == '0') {count++;}
        if (pMap[i-1][j] == '0') {count++;}
        if (count >= 1) {
            pMap[i][j] = '0';
        }
    }

    /* Check borders */

    i = 0;
    for (j=1; j<nMapWidth-1; j++) {
        if (worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
            count = 0;
            if (pMap[i][j-1] == '0') {count++;}
            if (pMap[i][j+1] == '0') {count++;}
            if (pMap[i+1][j] == '0') {count++;}
            if (count >= 2) {
                pMap[i][j] = '0';
            }
        }
    }

    i = nMapHeight-1;
    for (j=1; j<nMapWidth-1; j++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
            count = 0;
            if (pMap[i][j-1] == '0') {count++;}
            if (pMap[i][j+1] == '0') {count++;}
            if (pMap[i-1][j] == '0') {count++;}
            if (count >= 2) {
                pMap[i][j] = '0';
            }
        }
    }

    j = 0;
    for (i=1; i<nMapHeight-1; i++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
            count = 0;
            if (pMap[i][j+1] == '0') {count++;}
            if (pMap[i-1][j] == '0') {count++;}
            if (pMap[i+1][j] == '0') {count++;}
            if (count >= 2) {
                pMap[i][j] = '0';
            }
        }
    }

    j = nMapWidth-1;
    for (i=1; i<nMapHeight-1; i++) {
        if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {
            count = 0;
            if (pMap[i][j-1] == '0') {count++;}
            if (pMap[i-1][j] == '0') {count++;}
            if (pMap[i+1][j] == '0') {count++;}
            if (count >= 2) {
                pMap[i][j] = '0';
            }
        }
    }

    /* Check interior */

    bool deadend_exists = true;
    while (deadend_exists) {
        deadend_exists = false;
        for (i=1; i<nMapHeight-1; i++) {
            for (j=1; j<nMapWidth-1; j++) {
                if (! worth_checking(X1, Y1, X2, Y2, pMap, i, j)) {continue;}
                count = 0;
                if (pMap[i][j-1] == '0') {count++;}
                if (pMap[i][j+1] == '0') {count++;}
                if (pMap[i-1][j] == '0') {count++;}
                if (pMap[i+1][j] == '0') {count++;}
                if (count >= 3) {
                    /* There are 3 or more walls around this point, so it
                     * must be a dead end. Fill it in.
                     */
                    pMap[i][j] = '0';
                    deadend_exists = true;
                    /* If not a single deadend was found the iteration will
                     * stop.
                     */
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Hello ParadoxPath. \n";
    return 0;
}
