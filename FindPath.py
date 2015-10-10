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
def FindPath(
    nStartX, nStartY,
    nTargetX, nTargetY,
    nMapWidth, nMapHeight,
    pOutBuffer, nOutBufferSize
):

    # pMap = pMap.reshape(nMapHeight, nMapWidth)
    snake = [np.array([nStartY, nStartX])]
    forward(snake)


def forward(snake):

    global currentBest
    global currentBestSnake

    for prevPos in snake[:~0]:
        if (snake[~0] == prevPos).all():  # Been here before.
            return
    if len(snake) >= currentBest:  # A better solution has been found already.
        return
    elif len(snake) > nOutBufferSize:  # Snake is too long.
        return
    elif (snake[~0] == target).all():  # Victory!
        currentBest = len(snake)
        currentBestSnake = list(snake)
        return

    for direction in directions:
        newPos = snake[~0] + direction
        if pMap[newPos[0], newPos[1]]:  # if open path
            forward(snake + [newPos])  # continue moving


if __name__ == '__main__':

    pOutBuffer = []
    nOutBufferSize = 100
    nStartY, nStartX = 1, 1
    nTargetY, nTargetX = 2, 3
    nMapWidth, nMapHeight = 10, 10
    target = np.array([nTargetY, nTargetX])
    directions = np.array([[0,1], [1,0], [0,-1], [-1,0]])
    # pMap = pMap.reshape(nMapHeight, nMapWidth)
    pMap = np.array([
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
        [0, 1, 1, 0, 0, 0, 0, 0, 0, 0, ],
        [0, 1, 0, 1, 1, 1, 1, 1, 0, 0, ],
        [0, 1, 0, 1, 0, 1, 0, 1, 0, 0, ],
        [0, 1, 1, 1, 1, 1, 0, 1, 0, 0, ],
        [0, 1, 0, 0, 0, 1, 1, 1, 0, 0, ],
        [0, 1, 1, 1, 1, 1, 0, 0, 0, 0, ],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
    ])

    currentBest = np.inf
    currentBestSnake = None

    FindPath(
        nStartX, nStartY,
        nTargetX, nTargetY,
        nMapWidth, nMapHeight,
        pOutBuffer, nOutBufferSize
    )

    print currentBest
    print currentBestSnake
