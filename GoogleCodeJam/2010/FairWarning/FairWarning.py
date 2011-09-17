#!/usr/bin/env python

# I had to move to my immature python skills when C++ was not
#   providing me good (infinite length) data types. :(

# FIXME: I am not checking the GCD of the previous inputs itself.

import sys
import math
import fractions

def TimeToApocalypse(inputList):
	newInputList = inputList[:]
	inputList = list(set(inputList))
	if len(inputList) <= 1:
		# No hits here
#		print "Return point 1:", newInputList
		return 0
	inputList.sort()
#	print "Sorted input: ", inputList

	# Below is a break-fix
	firstGreatestCommonDivisor = inputList[0]
	for i in range(len(inputList)):
		firstGreatestCommonDivisor = fractions.gcd(firstGreatestCommonDivisor, inputList[i])

#	if firstGreatestCommonDivisor > 1:
#		print "Check 1:", firstGreatestCommonDivisor, inputList

	for i in range(len(inputList) - 1):
		difference = int(inputList[i + 1]) - int(inputList[i])

		if(i == 0):
			greatestCommonDivisor = difference

		if difference == 0:
			continue

		greatestCommonDivisor = fractions.gcd(greatestCommonDivisor, difference)
#		print "greatestCommonDivisor: ", greatestCommonDivisor, difference

	if greatestCommonDivisor == 1:
		# Validated all hits from here
#		print "GCD is 1: ", newInputList
		if firstGreatestCommonDivisor > 1:
			print "GCD is of first", firstGreatestCommonDivisor, newInputList
			return 0
		return 0

#	print "greatestCommonDivisor:", greatestCommonDivisor

	# FIXME: Temporary for fast computation.
#	if greatestCommonDivisor > 100000:
#		return -1

#	newGCD = 0
#	index = 0
#	for i in range(greatestCommonDivisor + 1):
#		thisGCD = inputList[0] + i
#		for j in range(len(inputList)):
#			thisGCD = fractions.gcd(thisGCD, inputList[j] + i)
#		if thisGCD > newGCD:
#			newGCD = thisGCD
#			index = i

	timeToApocalypse = greatestCommonDivisor - (inputList[0] % greatestCommonDivisor)

	newGreatestCommonDivisor = inputList[0] + timeToApocalypse
	for i in range(len(inputList)):
		newGreatestCommonDivisor = fractions.gcd(newGreatestCommonDivisor, inputList[i] + timeToApocalypse)

	# Added "=" after many many tests. Phew. This missing "=" was hard.
	if firstGreatestCommonDivisor >= newGreatestCommonDivisor:
		print "Check 2:", firstGreatestCommonDivisor, newGreatestCommonDivisor
		timeToApocalypse = 0

#	print "greatestCommonDivisor: ", greatestCommonDivisor
#	print "inputList[0]: ", inputList[0]
#	print "(inputList[0] % greatestCommonDivisor): ", (inputList[0] % greatestCommonDivisor)
#	print "timeToApocalypse: ", timeToApocalypse

#	if index != timeToApocalypse:
#		print "newIndex:", index, "oldIndex:", timeToApocalypse, inputList
#		print "firstGCD:", firstGreatestCommonDivisor, "newGCD:", newGCD, "newGreatestCommonDivisor:", newGreatestCommonDivisor

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
	testInput = inFile.readline().split()

	if len(testInput) <= 0:
		print "Bad testInput"
		quit(3)

	numberOfInputs = int(testInput[0])

	integralInputList = [int(word) for word in testInput[1:]]

	if numberOfInputs != len(integralInputList):
		print "Bad integralInputList"
		quit(3)

	outputString = "Case #" + str(currentTestCase) + ": " + str(TimeToApocalypse(integralInputList)) + "\n"
#	print outputString,
	outFile.write(outputString)

outFile.close()
inFile.close()
