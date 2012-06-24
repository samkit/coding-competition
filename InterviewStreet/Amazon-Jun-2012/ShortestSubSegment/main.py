#!/usr/bin/env python

import sys
sys.setrecursionlimit(200000000)

import pprint
import re

words = re.sub('[^a-zA-Z\s]', '', sys.stdin.readline()).rstrip('\n')
words_lc = words.lower()

wordCountsCache = {}

#tre = re.compile('\s')
#match = tre.search(words)
#offset = 0
#while match:
#    span = match.span()[0]
#    wordCountsCache[offset + span] = len(words[:offset + span].split())
#    match = tre.search(words[offset + span + 1:])
#    offset += span + 1
#
#wordCountsCache[0] = 0
#wordCountsCache[len(words)] = len(words.split())

K = int(sys.stdin.readline())

toSearch = []
for i in xrange(K):
    toSearch.append([ sys.stdin.readline().split()[0], []])

def search_pattern(line, pattern, start):
    result = []
    position = None
    while position is None and start < len(line):
        position = line.find(pattern, start)
        if (position == 0 or (position > 0 and line[position - 1].isspace())) \
            and \
            ((position + len(pattern)) >= len(line) or ((position + len(pattern)) < len(line) and line[position + len(pattern)].isspace())):
            break
        elif position == -1:
            position = None
            break
        else:
            start = position + 1
            position = None

    if position is not None:
        start = position
        end = start + len(pattern)
        result = [ [ start, end ] ]
        result.extend(search_pattern(line, pattern, end))

    return result

for pattern in toSearch:
    pattern[1].extend(search_pattern(words_lc, pattern[0], 0))
    if len(pattern[1]) == 0:
        print 'NO SUBSEGMENT FOUND'
        sys.exit(0)

wordBounds = [ [ 0, len(words) + 1 ] ]
[ wordBounds.extend(i[1]) for i in toSearch ]
for word in wordBounds:
    wordCountsCache[word[0]] = len(words[:word[0]].split())
    wordCountsCache[word[1]] = len(words[:word[1]].split())

#pprint.pprint(wordCountsCache, width = 200)
def get_words_in_between(words, considered):
    start = min([ i[0] for i in considered ])
    end = max([ i[1] for i in considered ])

    paraLength = wordCountsCache[end] - wordCountsCache[start]
    return paraLength, (start, end)

def for_each_position(words, toSearch, considered, minima):
    if len(toSearch) == len(considered):
        paraLength, para = get_words_in_between(words, considered)
        if minima[0] is None or minima[0] > paraLength:
            minima[0] = paraLength
            minima[1] = para
        return

    for position in toSearch[len(considered)][1]:
        copy = [ position ]
        copy.extend(considered)
        for_each_position(words, toSearch, copy, minima)

minimum = [None, '']
for_each_position(words, toSearch, [], minimum)
print words[minimum[1][0]:minimum[1][1]]
