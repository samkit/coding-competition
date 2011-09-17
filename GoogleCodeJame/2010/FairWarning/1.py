#!/usr/bin/env python

import fractions
import sys

# 66140856 66140856 33070428

if len(sys.argv) <= 2:
	print "Usage:", sys.argv[0], "toAdd number1 number2 number3 ..."
	quit(1)

toAdd = int(sys.argv[1])
numbers = sys.argv[2:]

gcd = int(numbers[0])
for i in range(len(numbers)):
	gcd = fractions.gcd(gcd, int(numbers[i]))

print "Before:", gcd

gcd = int(numbers[0]) + toAdd
for i in range(len(numbers)):
	gcd = fractions.gcd(gcd, int(numbers[i]) + toAdd)

print "After:", gcd
