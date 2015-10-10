import numpy as np
from FindPath import FindPath


pOutBuffer = []

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

print FindPath(
    nStartX = 1,
    nStartY = 1,
    nTargetX = 3,
    nTargetY = 2,
    pMap = pMap,
    nMapWidth = 10,
    nMapHeight = 10,
    pOutBuffer = pOutBuffer,
    nOutBufferSize = 100,
)
print pOutBuffer
