#!/usr/bin/env python

import sys

def splitPaths(paths):
	paths = [ path.split('/') for path in  paths ]
	return paths

def getCount(present, create):

	present = splitPaths(present)
	create = splitPaths(create)

	present_fs = { }
	for i in range(len(present)):
		index = present_fs
		for j in range(len(present[i])):
			if len(present[i][j]) <= 0:
				continue
			if present[i][j] not in index:
				index[ present[i][j] ] = { }
				index = index[ present[i][j] ]
			else:
				index = index[ present[i][j] ]

	count = 0
	
	for i in range(len(create)):
		index = present_fs
		for j in range(len(create[i])):
			if len(create[i][j]) <= 0:
				continue

			if create[i][j] not in index:
				index[ create[i][j] ] = { }
				index = index[ create[i][j] ]
				count += 1
			else:
				index = index[ create[i][j] ]
			
	return count
# Main

if len(sys.argv) != 2:
	print "error usage"
	quit(1)

try:
	inFile = open(sys.argv[1])
	outFile = open('output', 'w')
except IOError:
	print "error file"
	quti(2)

testCases = int(inFile.readline())

for current in range(testCases):
	params = [ int(word) for word in inFile.readline().split() ]
	present_int = params[0]
	create_int = params[1]

	present = []
	create = []
	
	for i in range(present_int):
		present.append(inFile.readline().strip('\n'))

	for i in range(create_int):
		create.append(inFile.readline().strip('\n'))

	output = 'Case #' + str(current + 1) + ': ' + str(getCount(present, create)) + '\n'
	print output,
	outFile.write(output)

inFile.close()
outFile.close()
