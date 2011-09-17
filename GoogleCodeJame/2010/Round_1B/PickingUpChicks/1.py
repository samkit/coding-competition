#!/usr/bin/env python

import sys

def willIntersectAfter(position, speed, i, j):
	time = 9999999
	if not (i not in range(len(position)) or j not in range(len(position))):
		if speed[i] == speed[j]:
			time = 0
		elif not (speed[i] < speed[j] and position[i] < position[j]):
			time = abs(position[i] - position[j]) / abs(speed[i] - speed[j])
	return time

def swap(position, speed, originalSpeeds, i, j):
#	print 'swap: '
#	print i, j

	if i not in range(len(position)) or j not in range(len(position)):
		return 0

	tempPosition = position[i]
	tempSpeed = speed[i]
	tempOriginalSpeed = originalSpeeds[i]

	position[i] = position[j]
	speed[i] = speed[j]
	originalSpeeds[i] = originalSpeeds[j]
	
	position[j] = tempPosition
	speed[j] = tempSpeed
	originalSpeeds[j] = tempOriginalSpeed

	speed[j] = originalSpeeds[j]

	return 1

def swapIfPossible(position, speed, originalSpeeds, time):
#	print '+++++++++++++++'
#	print position
#	print speed
#	print '+++++++++++++++'

	count = 0

	for i in range(len(position) - 1):
		if speed[i] != originalSpeeds[i]: # should be <
			timeOfIntersection_1 = 9999999
			timeOfIntersection_2 = 9999999
			if position[i] == position[i + 1]:
				timeOfIntersection_1 = willIntersectAfter(position, originalSpeeds, i, i + 2)
			if (i - 2) in range(len(position)) and position[i - 1] == position[i]:
				timeOfIntersection_2 = willIntersectAfter(position, originalSpeeds, i, i - 2)

			if timeOfIntersection_1 < timeOfIntersection_2:
				count += swap(position, speed, originalSpeeds, i, i + 1)
			elif timeOfIntersection_2 < timeOfIntersection_1:
				count += swap(position, speed, originalSpeeds, i, i - 1)
#			print "=============="
#			print position
#			print speed
#			print originalSpeeds
#			print count
#			print "=============="
			return count

			
def getIntersection(position, speed, originalSpeeds, time):
#	intersectTime = { }
	count = 0
	for i in range(len(position) - 1):
		if speed[i] == speed[i + 1]:
			continue
			
		if position[i] == position[i + 1] and speed[i] != speed[i + 1]:
			if speed[i] > speed[i + 1]:
				speed[i] = speed[i + 1]
			else:
				speed[i + 1] = speed[i]
			count += swapIfPossible(position, speed, originalSpeeds, time)
			continue

	return count
#		if speed[i] < speed[i + 1] and position[i] < position[i + 1]:
#			continue
#
#		intersectTime[ i ] = abs(position[i] - position[i + 1]) / abs(speed[i] - speed[i + 1])
#	return intersectTime

def updatePosition(position, speed, seconds, distance):
	for i in range(len(position)):
		newPosition = position[i] + speed[i] * seconds
		if newPosition > distance:
			newPosition = distance

		position[i] = newPosition

def countFinished(position, distance):
	count = 0
	for i in range(len(position)):
		if position[i] >= distance:
			count += 1

	return count

def getSwaps(minimum, distance, time, position, speed):
	originalSpeeds = speed[:]
	
	for i in range(len(position)):
		individualTimeRequired = (distance - position[i]) / speed[i]

	count = 0
	while time > 0:
		count += getIntersection(position, speed, originalSpeeds, time)
		updatePosition(position, speed, 1, distance)
		if countFinished(position, distance) >= minimum:
			break
		time -= 1
		
#	print position
#	print speed
#	print count

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

	totalChicks = params[0]
	minimum = params[1]
	distance = params[2]
	time = params[3]

	position = [ int(word) for word in inFile.readline().split() ]
	speed = [ int(word) for word in inFile.readline().split() ]

	output = 'Case #' + str(current + 1) + ': ' + str(getSwaps(minimum, distance, time, position, speed)) + '\n'
	print output,
	outFile.write(output)

inFile.close()
outFile.close()
