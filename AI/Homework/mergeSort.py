#--coding: utf8 --

import random
L=[random.randint(0,100000) for i in range(1024)]

def mergeSort(L):
    if len(L) <= 1:
        return L
    return merge(mergeSort(L[:len(L)/2]),mergeSort(L[len(L)/2:]))

def merge(left,right):
    tempList = []
    while not (len(left) == 0 or len(right) == 0):
        tempList.append(left.pop(0)
                        if left[0] < right[0]
                      else right.pop(0))
    tempList.extend(left)
    tempList.extend(right)

    return tempList

sortedList = mergeSort(L)
print "Random list:" , L
print "Sorted list:" , sortedList
    
            
        
            
