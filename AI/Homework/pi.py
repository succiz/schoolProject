#--coding: utf8 --

import math

n = int(raw_input("Please Enter a integer:"))

def findPi(n):
    summation = 1
    if n == 0 or n == 1:
        summation = 1
    else:
        for counter in range(2,n+1):
            t = (1+math.pow(2,counter-1))*math.pow(3,counter-1)
            summation = summation + math.pow((-1),(counter-1))/t
    pi = math.sqrt(12)*summation
    return pi
print findPi(n)
# when n is greater than 600, it will be overflow
