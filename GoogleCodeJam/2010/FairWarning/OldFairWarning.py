#!/usr/bin/env python

# I had to move to my immature python skills when C++ was not
#   providing me good (infinite length) data types. :(

import sys
import math
import fractions

def TimeToApocalypse(inputList):
	if len(inputList) <= 1:
		return 0

	inputList.sort()

#	print "Sorted input: ", inputList

	for i in range(len(inputList) - 1):
		difference = int(inputList[i + 1]) - int(inputList[i])

		if(i == 0):
			greatestCommonDivisor = difference

		if difference == 0:
			continue

		greatestCommonDivisor = fractions.gcd(greatestCommonDivisor, difference)
#		print "greatestCommonDivisor: ", greatestCommonDivisor, difference

	if greatestCommonDivisor == 1:
		return 0

	timeToApocalypse = greatestCommonDivisor - (inputList[0] % greatestCommonDivisor)

#	print "greatestCommonDivisor: ", greatestCommonDivisor
#	print "inputList[0]: ", inputList[0]
#	print "(inputList[0] % greatestCommonDivisor): ", (inputList[0] % greatestCommonDivisor)
#	print "timeToApocalypse: ", timeToApocalypse

	return timeToApocalypse

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
	outputString = "Case #" + str(currentTestCase) + ": " + str(TimeToApocalypse(integralInputList)) + "\n"
#	print outputString
	outFile.write(outputString)

outFile.close()
inFile.close()
