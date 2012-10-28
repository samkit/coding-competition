#!/usr/bin/env python

import sys

def custom_sort(array):
    for i in xrange(len(array)):
        toMove = array[i]
        if toMove is None:
            continue

        j = i
        valid = j
        while j > 0:
            k = array[j - 1]
            if k is None:
                pass
            elif toMove > k:
                break
            else:
                array[valid] = k
                valid = j - 1
            j -= 1
        array[valid] = toMove

    return array

def extract_connected(rules, start, output):
    output.add(start)
    for i in rules[start]:
        if rules[start][i] and i not in output:
            extract_connected(rules, i, output)

def get_connected_sets(rules):
    array = []
    for i in rules:
        extract = True
        for s in array:
            if i in s:
                extract = False
                break
        if not extract:
            continue
        output = set()
        extract_connected(rules, i, output)
        array.append(output)
    return array

inFile = sys.stdin
outFile = sys.stdout

K = int(inFile.readline())
P = [ int(i) for i in inFile.readline().split() ]

rules = dict()

for i in xrange(K):
    rules[i] = dict()
    rule = [ t == 'Y' for t in inFile.readline().rstrip() ]
    for j in xrange(len(rule)):
        rules[i].update({ j : rule[j] })

connected = get_connected_sets(rules)

for s in connected:
    array = [ P[i] if i in s else None for i in xrange(len(P)) ]
    custom_sort(array)
    P = [ array[i] if array[i] else P[i] for i in xrange(len(array)) ]

for i in P:
    print i,
print
