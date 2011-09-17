#!/bin/env python

# this is not complete !!!

import sys

def cost(numbers, delete, insert, maximum):
	print 'params: ', delete, insert, maximum

	cost = 0

	i = 0
	while i < (len(numbers) - 1):

		print numbers

		insert_cost = 9999
		delete_cost = 9999
		change_cost = 9999

#		print i, len(numbers)
		difference = abs(numbers[i] - numbers[i + 1])
		if difference <= maximum:
			i += 1	# bad coding
			continue

		if maximum > 0:
			missing = abs(difference) / maximum
			print 'diff: ', difference, 'missing: ', missing
			insert_cost = missing * insert

		delete_cost = delete

		change_cost = abs(difference) - maximum

		print delete_cost
		print insert_cost
		print change_cost

		if min(delete_cost, insert_cost, change_cost) == delete_cost:
			if (i + 2) in range(len(numbers)):
				difference_2 = abs(numbers[i + 1] - numbers[i + 2])
				difference_3 = abs(numbers[i] - numbers[i + 2])
				if difference_2 > difference_3:
					numbers.pop(i + 1)
				else:
					numbers.pop(i) # if removing this element, then check previous and next entry
			else:
				numbers.pop(i)
			cost += delete_cost
			continue # do not increment counter `i'
		elif min(delete_cost, insert_cost, change_cost) == insert_cost:
			cost += insert_cost
		elif min(delete_cost, insert_cost, change_cost) == change_cost:
			if (i + 2) in range(len(numbers)):
				difference_2 = abs(numbers[i + 1] - numbers[i + 2])
				difference_3 = abs(numbers[i] - numbers[i + 2])

				if difference > difference_3:
					# transit towards 3rd block
					if numbers[i] > numbers[i + 2]:
						numbers[i] =
				
				if numbers[i] > numbers[i + 1] and numbers[i + 2] > numbers[i + 1]:
					numbers[i + 1] = numbers[i] + maximum
				elif numbers[i] < numbers[i + 1] and numbers[i + 2] < numbers[i + 1]:
					numbers[i + 1] = numbers[i] - maximum
				else:
					numbers[i] = numbers[i + 1] - maximum
			cost += change_cost

		i += 1

#	print 'Total cost: ', cost
	return cost
## Main

if len(sys.argv) != 2:
	print "error"
	quit(1)

try:
	inFile = open(sys.argv[1])
	outFile = open('output', 'w')
except IOError:
	print "Error"
	quit(2)

totalTestCases = int(inFile.readline())

current = 0

while totalTestCases > 0:
	totalTestCases -= 1
	current += 1
	line = inFile.readline().split()
	delete = int(line[0])
	insert = int(line[1])
	maximum = int(line[2])
	totalNumbers = int(line[3])

	numbers = [int(number) for number in inFile.readline().split()]

	output = "Case #" + str(current) + ": " + str(cost(numbers, delete, insert, maximum)) + "\n"
	print output,
	outFile.write(output)
	outFile.flush()

outFile.close()
inFile.close()
