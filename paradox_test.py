import numpy as np
from FindPath import FindPath

### Example 1:
"""pMap = (
"0000000000011000000001011111000101010100011111010001000111000111110000010000000001000000000000000000"
)"""
###

### Example 2:
"""pMap = [
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
]"""

Nx = 12
Ny = 12

### Example 3:
pMap = np.random.randint(4, size=Nx*Nx)
pMap[np.where(pMap > 1)] = 1
###

x0 = np.random.randint(Nx)
y0 = np.random.randint(Nx)
x = np.random.randint(Nx)
y = np.random.randint(Nx)
pMap[y0*Nx + x0] = 1
pMap[y*Nx + x] = 1

pOutBuffer = []

print "Shortest path, length and indices:"
print FindPath(
    nStartX = x0,
    nStartY = y0,
    nTargetX = x,
    nTargetY = y,
    pMap = pMap,
    nMapWidth = Nx,
    nMapHeight = Ny,
    pOutBuffer = pOutBuffer,
    nOutBufferSize = 1000,
)
print pOutBuffer
