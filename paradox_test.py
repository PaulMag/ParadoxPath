import numpy as np
from FindPath import FindPath

pMap = (
"0000000000011000000001011111000101010100011111010001000111000111110000010000000001000000000000000000"
)
# pMap = [
    # 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    # 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    # 0, 1, 0, 1, 1, 1, 1, 1, 0, 0,
    # 0, 1, 0, 1, 0, 1, 0, 1, 0, 0,
    # 0, 1, 1, 1, 1, 1, 0, 1, 0, 0,
    # 0, 1, 0, 0, 0, 1, 1, 1, 0, 0,
    # 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    # 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    # 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    # 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
# ]

pOutBuffer = []

print "Shortest path, length and indices:"
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
