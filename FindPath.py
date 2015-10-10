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

currentBest = np.inf
currentBestSnake = []
directions = np.array([[0,1], [1,0], [0,-1], [-1,0]])
pMapGlobal = None
target = None
nOutBufferSizeGlobal = None


def FindPath(
    nStartX, nStartY,
    nTargetX, nTargetY,
    pMap, nMapWidth, nMapHeight,
    pOutBuffer, nOutBufferSize
):

    if isinstance(pMap, basestring):
        pMap = np.array(list(pMap)).astype(bool)
    else:
        pMap = np.array(pMap).astype(bool)

    pMap = pMap.reshape(nMapHeight, nMapWidth)
    global pMapGlobal
    pMapGlobal = pMap
    global target
    target = np.array([nTargetY, nTargetX])
    global nOutBufferSizeGlobal
    nOutBufferSizeGlobal = nOutBufferSize

    snake = [np.array([nStartY, nStartX])]
    forward(snake)

    if np.isinf(currentBest):
        return -1
    else:
        for pos in currentBestSnake[1:]:  # Do not count start position.
            pOutBuffer.append(pos[0]*nMapWidth + pos[1])
        return currentBest - 1


def forward(snake):

    global currentBest
    global currentBestSnake

    for prevPos in snake[:~0]:
        if (snake[~0] == prevPos).all():  # Been here before.
            return
    if len(snake) >= currentBest:  # A better solution has been found already.
        return
    elif len(snake) > nOutBufferSizeGlobal:  # Snake is too long.
        return
    elif (snake[~0] == target).all():  # Victory!
        currentBest = len(snake)
        currentBestSnake = list(snake)
        return

    for direction in directions:
        newPos = snake[~0] + direction
        if pMapGlobal[newPos[0], newPos[1]]:  # if open path
            forward(snake + [newPos])  # continue moving
