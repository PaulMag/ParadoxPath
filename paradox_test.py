import numpy as np
from FindPath import FindPath

# pMap = (
# "0000000000011000000001011111000101010100011111010001000111000111110000010000000001000000000000000000"
# )
N = 25
x0 = np.random.randint(N)
y0 = np.random.randint(N)
x = np.random.randint(N)
y = np.random.randint(N)
pMap = np.random.randint(4, size=N*N)
pMap[np.where(pMap > 1)] = 1
pMap[y0*N + x0] = 1
pMap[y*N + x] = 1
# print pMap.reshape(N, N)[:10, :10]
# pMap = [
    # 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    # 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    # 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    # 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    # 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    # 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
    # 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    # 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    # 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
    # 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
# ]

pOutBuffer = []

print "Shortest path, length and indices:"
print FindPath(
    nStartX = x0,
    nStartY = y0,
    nTargetX = x,
    nTargetY = y,
    pMap = pMap,
    nMapWidth = N,
    nMapHeight = N,
    pOutBuffer = pOutBuffer,
    nOutBufferSize = int(N**1.5),
)
print pOutBuffer
