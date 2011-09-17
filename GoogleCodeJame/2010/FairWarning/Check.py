#!/usr/bin/env python

# I had to move to my immature python skills when C++ was not
#   providing me good (infinite length) data types. :(

import sys
import math
import fractions

def TimeToApocalypse(inputList):
	gcd = inputList[0]
	for i in range(len(inputList)):
		gcd = fractions.gcd(gcd, inputList[i])

	index = 0

	i = 0
	while i < 86955513:
		newGCD = inputList[0] + i

		j = 0
		while j < len(inputList):
			newGCD = fractions.gcd(newGCD, inputList[j] + i)
			j += 1

		if newGCD > gcd:
			gcd = newGCD
			index = i

		i += 1

	return index

# Main function
if len(sys.argv) != 2:
	print "Usage: ", sys.argv[0], " <input file>"
	quit(1)

try:
	inFile = open(sys.argv[1])
except IOError:
	print "Error opening input file: ", sys.argv[1]
	quit(2)

try:
	outFile = open('output', 'w')
except IOError:
	print "Error opening output file"
	quit(2)

currentTestCase = 0

numberOfTestCases = int(inFile.readline())
while numberOfTestCases > 0:
	numberOfTestCases -= 1
	currentTestCase += 1
	testInputLine = inFile.readline()
	testInput = testInputLine.split()
	numberOfInputs = int(testInput[0])
	integralInputList = [int(word) for word in testInput[1:]]

	if currentTestCase < 11:
		continue

	outputString = "Case #" + str(currentTestCase) + ": " + str(TimeToApocalypse(integralInputList)) + "\n"
	print outputString
#	print outputString
	outFile.write(outputString)
	outFile.flush()

outFile.close()
inFile.close()
