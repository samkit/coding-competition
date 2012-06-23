#!/usr/bin/env python

import sys
sys.setrecursionlimit(1010 * 1010)

neighbours = (
    ( -1, -1 ),
    ( -1,  0 ),
    ( -1,  1 ),
    (  0, -1 ),
    (  0,  1 ),
    (  1, -1 ),
    (  1,  0 ),
    (  1,  1 ),
)

def clear_array(array, x, y):
    if array[x][y] != 1:
        return 0
    array[x][y] = 0
    for neighbour in neighbours:
        i = x + neighbour[0]
        j = y + neighbour[1]
        if 0 <= i and i < len(array) and 0 <= j and j < len(array):
            clear_array(array, i, j)
    return 1

T = int(sys.stdin.readline())

for iT in xrange(T):
    N = int(sys.stdin.readline())
    array = []
    for iN in xrange(N):
        array.append([ int(i) for i in sys.stdin.readline().split() ])

    count = 0
    for iN_1 in xrange(N):
        for iN_2 in xrange(N):
            count += clear_array(array, iN_1, iN_2)
    print count
