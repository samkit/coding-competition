#!/usr/bin/env python

import sys

def get_matching_bracket(line, start, count):
    if start >= len(line):
        return -1
    elif line[start] == '(':
        return get_matching_bracket(line, start + 1, count + 1)
    elif line[start] == ')':
        if count == 1:
            return start
        else:
            return get_matching_bracket(line, start + 1, count - 1)
    else:
        return get_matching_bracket(line, start + 1, count)

def get_one_node(line, start):
    if start >= len(line):
        return -1, None

    if line[start] == '(':
        end = get_matching_bracket(line, start, 0)
        if end == -1:
            return -1, None
        return line[start : end + 1], end + 1
    elif line[start] == ')':
        return -1, None
    elif line[start] == '0':
        return line[start], start + 1
    else:
        return -1, -1

def get_left_right(line):
    left, rightStart = get_one_node(line, 0)
    if rightStart is None:
        return -1, -1

    right, rightEnd = get_one_node(line, rightStart)
    if rightEnd is None:
        return -1, -1

    if rightEnd <= len(line) - 1:
        return -1, -1

    return left, right

# ((00)(00))
# (00)
def get_depth(line):
    if line[0] == '(':
        end = get_matching_bracket(line, 0, 0)
        if end == -1:
            return -1

        left, right = get_left_right(line[1:end])
        if -1 in (left, right):
            return -1

        leftDepth = get_depth(left)
        rightDepth = get_depth(right)

        if -1 in (leftDepth, rightDepth):
            return -1

        return 1 + max(get_depth(left), get_depth(right))

    else:
        return 0

depth = get_depth(sys.argv[1])
if depth != -1:
    depth -= 1
print depth
