#!/usr/bin/env python

import sys
sys.setrecursionlimit(100000)

import math

fibonacci_cache = {}
def get_fibonacci_number(i):
    if i in fibonacci_cache:
        return fibonacci_cache[i]

    if i <= 1:
        value = i
    else:
        value = get_fibonacci_number(i - 1) + get_fibonacci_number(i - 2)

    fibonacci_cache[i] = value
    return value

prime_cache = [ 2, 3, 5 ]
def build_prime_cache(maximum):
    def isPrime(n):
        for i in prime_cache:
            if i > math.sqrt(n):
                break
            if n % i == 0:
                return False
        return True

    i = 6
    count = 0
    while count <= maximum:
        if isPrime(i):
            prime_cache.append(i)
            count += 1
        i += 1

get_fibonacci_number(200)   # build up cache
build_prime_cache(100000)

fibonacci_numbers = list(fibonacci_cache)
fibonacci_numbers.sort()
fibonacci_numbers.remove(0)
fibonacci_numbers.remove(1)

def get_factors(num):
    factors = set()
    for i in prime_cache:
        if num % i == 0:
            factors.add(i)
            num /= i
        if num <= 1:
            break
    return factors

T = int(sys.stdin.readline())
for iT in range(T):
    K = int(sys.stdin.readline())
    factors = get_factors(K)
    for key in fibonacci_numbers:
        fibonacci = fibonacci_cache[key]
        f_factors = get_factors(fibonacci)
        intersection = factors.intersection(f_factors)
        if len(intersection) > 0:
            print fibonacci, min(intersection)
            break
