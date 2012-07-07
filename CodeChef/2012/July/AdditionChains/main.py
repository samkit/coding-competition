#!/usr/bin/env python

import sys

def get_max_power_of_2(number):
    # Any other way?
    length = len(bin(number))
    return int('1' + (length - 3) * '0', 2)

def print_chain(number, end):
    indexes = list()
    numberToIndex = dict()      # max 666 indexes utilization

    while number > end:
        first = get_max_power_of_2(number)
        second = number - first

        if first != number:
            numberToIndex[number] = len(indexes)
            indexes.append((first, second))

        while first > second:
            numberToIndex[first] = len(indexes)
            first /= 2
            if first:
                indexes.append((first, first))

        number = second

    count = len(indexes)
    print count
    while len(indexes):
        p = indexes.pop()
        print count - numberToIndex[p[0]], count - numberToIndex[p[1]]

N = int(raw_input())
print_chain(N, 0)

sys.exit(0)
