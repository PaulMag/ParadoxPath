import numpy as np


"""
The meaning of the parameters are as follows:

nStartX and nStartY are the 0-based coordinates of the start position.
nTargetX and nTargetY are the 0-based coordinates of the target position.
pMap describes a grid of width nMapWidth and height nMapHeight. The grid is
    given in row-major order, each row is given in order of increasing
    x-coordinate, and the rows are given in order of increasing y-coordinate.
    Traversable locations of the grid are indicated by 1, and impassable
    locations are indicated by 0. Locations are considered to be adjacent
    horizontally and vertically but not diagonally.
pOutBuffer is where you should store the positions visited in the found
    path, excluding the starting position but including the final position.
    Entries in pOutBuffer are indices into pMap.
nOutBufferSize is the maximum amount number of entries that can be written
    to pOutBuffer.
The function must return the length of the shortest path between Start and
    Target, or -1 if no such path exists.
If the shortest path is longer than nOutBufferSize, the calling function
    might either give up or choose to call FindPath again with a larger output
    buffer.

Constraints:
You may safely assume that:
1 <= nMapWidth, nMapHeight,
0 <= nStartX, nTargetX < nMapWidth,
0 <= nStartY, nTargetY < nMapHeight,
Both Start and Target are empty locations,
nOutBufferSize >= 0.

Additional considerations:
Consider performance, memory usage and assume that your code may be called
from a multi-threaded environment.
"""


class Maze():

    dir1 = np.array([+1,  0,  0, -1], dtype=int)
    dir2 = np.array([ 0, +1, -1,  0], dtype=int)


    def __init__(self,
        nStartX, nStartY,
        nTargetX, nTargetY,
        pMap, nMapWidth, nMapHeight,
    ):
        self.start  = np.array([nStartY,  nStartX ], dtype=int)
        self.target = np.array([nTargetY, nTargetX], dtype=int)

        if isinstance(pMap, basestring):
            pMap = np.array(list(pMap)).astype(bool)
        else:
            pMap = np.array(pMap).astype(bool)
        pMap = pMap.reshape(nMapHeight, nMapWidth)
        self.pMap = np.zeros((nMapHeight+1, nMapWidth+1))
        self.pMap[:~0, :~0] = pMap  # Make map with 0-padding.
        self.nMapWidth = nMapWidth

        self.directions = np.zeros((4, 2), dtype=int)


    def solve(self, pOutBuffer, nOutBufferSize):

        self.currentBest = np.inf
        self.currentBestSnake = []
        self.nOutBufferSize = nOutBufferSize
        self.forward([self.start])

        if np.isinf(self.currentBest):
            return -1
        else:
            for pos in self.currentBestSnake[1:]:  # Do not count start position.
                pOutBuffer.append(pos[0]*self.nMapWidth + pos[1])
            return len(pOutBuffer)


    def forward(self, snake):

        for prevPos in snake[:~0]:
            if (snake[~0] == prevPos).all():
                # Been here before.
                return
        best_possibility = len(snake) + np.abs(self.target - snake[~0]).sum()
        if best_possibility >= self.currentBest:
            # A better solution has been found already.
            return
        elif best_possibility > self.nOutBufferSize:
            # Snake is too long.
            return
        elif (snake[~0] == self.target).all():
            # Victory!
            self.currentBest = len(snake)
            self.currentBestSnake = list(snake)
            return

        self.set_direction(snake[~0])
        for direction in self.directions:
            newPos = snake[~0] + direction
            if self.pMap[newPos[0], newPos[1]]:  # if open path
                self.forward(snake + [newPos])  # continue moving


    def set_direction(self, head):

        direction = self.target - head
        i = np.argmax(np.abs(direction))

        if direction[i] >= 0:
            self.directions[:, i] = +self.dir1
        else:
            self.directions[:, i] = -self.dir1
        if direction[not i] >= 0:
            self.directions[:, not i] = +self.dir2
        else:
            self.directions[:, not i] =  -self.dir2


def FindPath(
    nStartX, nStartY,
    nTargetX, nTargetY,
    pMap, nMapWidth, nMapHeight,
    pOutBuffer, nOutBufferSize,
):
    mazeObj = Maze(
        nStartX, nStartY,
        nTargetX, nTargetY,
        pMap, nMapWidth, nMapHeight,
    )
    return mazeObj.solve(pOutBuffer, nOutBufferSize)
