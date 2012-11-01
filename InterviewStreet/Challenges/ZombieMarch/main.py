#!/usr/bin/env python

from pprint import pprint
import sys

inFile = sys.stdin

T = int(inFile.readline())

for t in xrange(T):
    N, M, K = [ int(i) for i in inFile.readline().split() ]

    grid = dict()
    for edge in xrange(M):
        start, end = [ int(z) for z in inFile.readline().split() ]
        if start not in grid:
            grid[start] = set()
        if end not in grid:
            grid[end] = set()
        grid[start].add(end)
        grid[end].add(start)

    population = dict()
    for node in xrange(N):
        population[node] = float(inFile.readline())

    for step in xrange(K):
        probabilities = dict()
        for node, neighbours in grid.iteritems():
            probabilities[node] = population[node] / len(neighbours)

        for node in xrange(N):
            population[node] = sum([ probabilities[neighbour] for neighbour in grid[node] ])

    result = [ int(round(z[1])) for z in sorted(population.iteritems(), key = lambda x: x[1], reverse = True)[:5] ]
    for z in result:
        print z,
    print
