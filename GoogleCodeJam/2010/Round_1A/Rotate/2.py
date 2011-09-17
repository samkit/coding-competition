#!/usr/bin/env python

# Very bad coding done with brute force.

import sys

def printLines(lines):
	print "==========================="
	for i in range(len(lines)):
		print i, lines[i].replace(' ', '-')
	print "==========================="

def maximumContinuation(countArray):
	print countArray
	max = 0
	for i in range(len(countArray)):
		if countArray[i] > 0:
			max += 1
		else:
			max = 0
	return max

def isWinning(lines, required, color):
	for i in range(len(lines)):
		lines[i] = lines[i].replace(' ', '').rjust(len(lines))

#	printLines(lines)

	count = 0
	for i in range(len(lines)):
		for j in range(len(lines)):
			if lines[i][j] == color:
				# Horizontal
				count = 1
				for k in range(i + 1, len(lines)):
					if lines[k][j] == color:
						count += 1
					else:
						break
				if count >= required:
#					print 'Horizontal'
					return True

				# Vertical
				count = 1
				for k in range(j + 1, len(lines)):
					if lines[i][k] == color:
						count += 1
					else:
						break
				if count >= required:
#					print 'Vertical'
					return True

				# Left to Right diagonal
				count = 1
				for to_add in [1, -1]:
					k = i + to_add
					l = j + to_add
					while k in range(len(lines)) and l in range(len(lines)):
#						print 'Right: ', k, l
						if lines[k][l] == color:
							count += 1
						else:
							break
						k += to_add
						l += to_add

				if count >= required:
#					print 'Rigth diagonal'
					return True

				# Right to Bottom Left diagonal
				count = 1
				for to_add in [1, -1]:
					k = i + to_add
					l = j - to_add
				while k in range(len(lines)) and l in range(len(lines)):
#					print 'Left: ', k, l
					if lines[k][l] == color:
						count += 1
					else:
						break
					k += to_add
					l -= to_add

				if count >= required:
#					print 'Left diagonal'
					return True

	return False

def whoWins(lines, required):
	red_won = isWinning(lines, required, 'R')
	blue_won = isWinning(lines, required, 'B')

	if red_won and blue_won:
		return "Both"
	elif red_won:
		return "Red"
	elif blue_won:
		return "Blue"

	return "Neither"

##########
##########
## Main ##
##########
##########

if len(sys.argv) != 2:
	print "Error in usage"
	quit(1)

try:
	inFile = open(sys.argv[1])
	outFile = open('output', 'w')
except IOError:
	print "File I/O error"
	quit(2)

testCases = int(inFile.readline())
for currentTestCase in range(testCases):
	parameters = [int(word) for word in inFile.readline().split()]

	lines = []
	for i in range(parameters[0]):
		lines.append(inFile.readline().replace('.', ' ').strip('\n'))

	output = "Case #" + str(currentTestCase + 1) + ": " + whoWins(lines, parameters[1]) + "\n"
	outFile.write(output)

inFile.close()
outFile.close()
