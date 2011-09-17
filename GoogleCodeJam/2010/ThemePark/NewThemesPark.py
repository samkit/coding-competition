#!/usr/bin/env python

import sys
from collections import deque

def CreateCyclicQueues(groups):
	cyclicQueues = []

	deq = deque(groups)
	for i in range(len(groups)):
		cyclicQueues.append(list(deq)[:])
		deq.rotate(-1)

	return cyclicQueues


def CreateSummaryOfGroups(capacity, groups):
	allGroupsSummary = []

	for i in range(len(groups)):
		groupSummary = []
		total = 0
		for j in range(len(groups[i])):
			total += groups[i][j]
			if total > capacity:
				break
			groupSummary.append(total)
		allGroupsSummary.append(groupSummary)
	return allGroupsSummary


def CalculateEarning(numberOfRounds, capacity, groups):

	groups = CreateCyclicQueues(groups)

	allGroupsSummary = CreateSummaryOfGroups(capacity, groups)

#	print allGroupsSummary

	earnings = 0
	nextGroup = 0

	index  = 0

	while numberOfRounds > 0:

#		print index, len(allGroupsSummary)
		if (len(allGroupsSummary) < numberOfRounds) and (index >= len(allGroupsSummary)):
			earnings += earnings * numberOfRounds
			break
			

		if len(allGroupsSummary[nextGroup]) == 0:
			# Skip the group whose size is greater than capacity
			#   and give chance to next group.
			nextGroup += 1

		else:
			earnings += allGroupsSummary[nextGroup][ len(allGroupsSummary[nextGroup]) - 1 ]
			nextGroup += len(allGroupsSummary[nextGroup])
			index += 1

		nextGroup %= len(allGroupsSummary)

		numberOfRounds -= 1

	return earnings

# Main function

if len(sys.argv) != 2:
	print "Usage: ", sys.argv[0], "<input file>"
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

line = inFile.readline().split()
numberOfTestCases = int(line[0])
currentTestCase = 0

while numberOfTestCases > 0:
	currentTestCase += 1
	words = inFile.readline().split() # Format: Rounds Capacity NumberOfGroups
	rkn = [int(number) for number in words]

	if len(rkn) != 3:
		print "Bad input in rkn"
		quit(3)

	words = inFile.readline().split() # Format: Group1 Group2 Group3 ...
	groups = [int(number) for number in words]

	if len(groups) != rkn[2]: # Sanity check
		print "Bad input in groups"
		quit(3)
	
	outputString = "Case #" + str(currentTestCase) + ": " + str(CalculateEarning(rkn[0], rkn[1], groups)) + "\n"

#	print outputString,

	outFile.write(outputString)

	numberOfTestCases -= 1

inFile.close()
outFile.close()
