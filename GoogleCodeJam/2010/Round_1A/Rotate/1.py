#!/usr/bin/env python

import sys

def rotate(array):
	for i in range(len(array)):
		for j in range(len(array)):
			print array[j][i],
		print

def rotateClockWise(array):
	length = len(array)
	for i in range(length):
		array[i] = array[i].rstrip().rjust(length)

	red_hor = []
	red_vert = []
	red_left_diag = []
	red_right_diag = []

	rotate(array)
	for i in range(length):
		count_hor = 0
		for j in range(length):
			if array[i][j] == 'R':
				if i + 1 < length:
					if array[i + i][j] == 'R':
						count_hor += 1
		


if len(sys.argv) != 2:
	print "Error in init"
	quit(1)

try:
	inFile = open(sys.argv[1])
#	outFile = open('output'
except IOError:
	print "Error opening file"
	quit(2)

i = 0
lines = []
while i < 6:
	line = inFile.readline()
	lines.append(line.replace('.', ' ').strip('\n'))
	i += 1

rotateClockWise(lines)
print lines
