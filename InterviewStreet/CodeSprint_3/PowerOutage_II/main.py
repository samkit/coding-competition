#!/usr/bin/env python

import sys
import pprint

def possible_paths(grid, source, destination, previous = None):
    if previous is None:
        previous = [ source ]
    output = list()
    outgoings = grid[source]
    for outgoing in outgoings:
        if outgoing in previous:
            continue
        tillHere = previous[:]
        tillHere.append(outgoing)
        if outgoing == destination:
            output.append(tillHere)
        else:
            subpaths = possible_paths(grid, outgoing, destination, tillHere)
            map(lambda subpath: output.append(subpath), subpaths)
    return output

def path_length(grid, path):
    length = 0
    previous = path[0]
    for i in path[1:]:
        length += grid[previous][i]
        previous = i
    return length

inFile = sys.stdin

N, M = [ int(i) for i in inFile.readline().split() ]

grid = dict()

for i in xrange(M):
    x, y, d = [ int(z) for z in inFile.readline().split() ]
    x -= 1
    y -= 1
    if x not in grid:
        grid[x] = dict()
    if y not in grid:
        grid[y] = dict()
    grid[x].update({ y : d })
    grid[y].update({ x : d })

L = [ int(i) for i in inFile.readline().split() ]
G = [ int(i) for i in inFile.readline().split() ]

costGrid = dict()

for generator in xrange(N):
    g_i = G[generator]
    costGrid[generator] = dict()
    for pole in xrange(N):
        paths = possible_paths(grid, generator, pole)
        if len(paths):
            minPath = reduce(lambda x, y: x if path_length(grid, x) < path_length(grid, y) else y, paths)
        else:
            minPath = None

        costGrid[generator][pole] = path_length(grid, minPath) * L[pole] if minPath else None

pprint.pprint(costGrid)

for pole in xrange(N):
    costs = map(lambda x: [ x[0], x[1][pole] ], costGrid.iteritems())
    print pole, costs
    preferred = list()

    def reducer(x, y):
        if x is None:
            return y
        if y is None:
            return x
        if x < y:
            return x
        return y
#   minCost = reduce(reducer, costs)
#   print pole, costs, '=====', minCost
