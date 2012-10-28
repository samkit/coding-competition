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

def less_cost_comparator(x, y):
    if x[1] is None:
        return 1
    if y[1] is None:
        return -1
    return x[1] - y[1]

def all_combinations(G, L, grid, level, deployed, costTillNow, minCost, *path):
    if level == len(grid):
        minCost[0] = min(minCost[0], costTillNow) if minCost[0] else costTillNow
        minCost[1] = path
        return

    for i in grid[level]:
        cost = L[level] * (i[1] if i[1] else 0)
        if i[0] not in [ z[1] for z in deployed.iteritems() ]:
            deployed[level] = i[0]
            cost += G[i[0]]
        if not (minCost[0] and minCost[0] < costTillNow + cost):
            all_combinations(G, L, grid, level + 1, deployed, costTillNow + cost, minCost, [ level, i[0] ], *path)
        deployed[level] = None

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

sortedGrids = dict()
for pole in xrange(N):
    costs = map(lambda x: [ x[0], x[1][pole] ], costGrid.iteritems())
    costs.sort(cmp = less_cost_comparator)
    sortedGrids[pole] = costs

minCost = [ None, None ]
all_combinations(G, L, sortedGrids, 0, {}, 0, minCost)

generators = set([ z[1] for z in minCost[1] ])
print len(generators)
for i in generators:
    print i + 1,
print
for i in sorted(minCost[1], key = lambda x: x[0]):
    print i[1] + 1,
print
