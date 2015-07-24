#Shuyi Zhao
#COSC 5354: Artificial Intelligence
#Due: Sep 30, 2011
#Project: Vacuum Cleaner World: part 2

#All the rooms are dirty at the begainning
#All the movements are random
#Agent cannot know the state of the whole enviroment

#--coding: utf8 --
#import :
import random
import os

# global variable
direction_list = ['left','right','up','down']
failure_chance = ['success','success','success','failure']

##define functions:

#####################################################################
##choose_direction fuction
##
##This fucntion choose a random direction that the vacuum will go to
##know the state of the whole enviroment

##Return: the direction it choosed
##
##Reference Parameters: NONE
#####################################################################
def choose_direction():
   return random.choice(direction_list)

#####################################################################
##murphys_law fuction
##
##This fucntion makes a room has 25% opportunity became dirty or did
##not clean
##
##Return: rooms
##
##Reference Parameters: a, b, rooms
#####################################################################
def murphys_law(a, b, rooms):
    choice = random.choice(failure_chance)
    if choice == 'failure':
        rooms[a][b] = 0
    return rooms

#####################################################################
##oracle fuction
##
##This fucntion can scan all rooms to see if they are clean
##
##Return: state
##
##Reference Parameters: state, rooms
#####################################################################
def oracle(state, rooms):
    for i in range(7):
        for j in range(7):
            if rooms[i][j] == 0:
                return state
    state = True
    return state

#####################################################################
##is_clean fuction
##
##This fucntion hardcode 10 blocks in 100 rooms, meanwhile all the
##blocks and rooms are reachable
##
##Return: sucks, rooms
##
##Reference Parameters: x, y, sucks, rooms
#####################################################################
def is_clean(x, y, unsucks, sucks, rooms):
    if rooms[x][y] == 0:
       sucks = sucks + 1
       rooms[x][y] = 1
    else:
       unsucks = unsucks + 1
    return sucks, unsucks, rooms

#####################################################################
##action fuction
##
##This fucntion is to go to the next positon
##
##Return: x, y
##
##Reference Parameters: x, y, direction
#####################################################################    
def action(x, y, direction):
    if direction == 'left':
        y = y - 1
    elif direction == 'right':
        y = y + 1
    elif direction == 'up':
        x = x - 1
    elif direction == 'down':
        x = x + 1
    return x, y
       
#####################################################################
##agent fuction
##
##This fucntion is to action like a agent: get the current state,
##clean, go to the next position
##
##Return: x, y, sucks, bumps, moves, a, b, rooms 
##
##Reference Parameters: x, y, sucks, bumps, moves, rooms
#####################################################################
def agent(x, y, sucks, unsucks, bumps, moves, rooms):
   #percept the state
    a = x
    b = y
    sucks, unsucks, rooms = is_clean(x, y, sucks, unsucks, rooms)

   #go to the next room
    direction = choose_direction()
    x, y = action(x, y, direction)
    
   #hit the wall, do not change positon and state
    if (direction == 'up' or direction == 'down') and (x > 6 or x < 0):
            x = a
            bumps = bumps + 1
          
    elif (direction == 'left' or direction == 'right') and (y > 6 or y < 0):
            y = b
            bumps = bumps + 1
    else:
        moves = moves+1
        
    return x, y , sucks, unsucks, bumps, moves, a, b, rooms 

def main():
    rooms = [[0 for i in range(7)] for j in range(7)]
    x = 0
    y = 0
    sucks = 0
    unsucks = 0
    bumps = 0
    moves = 0
    state = False
    
    while not state:
        if moves != 0 and ( x != a or y != b):
            rooms = murphys_law(a, b, rooms)
        x, y , sucks, unsucks, bumps, moves, a, b, rooms = agent(x, y, sucks, unsucks, bumps, moves, rooms)
 
        if moves%100000 == 0:
           #print rooms
           displayRooms = [['#' if rooms[i][j] == 0 else ' ' for i in range(7)] for j in range(7)]
           displayRooms[x][y] = '@'
           outputRooms = ''
           for i in range(7):
             for j in range(7):
                outputRooms += str(displayRooms[i][j])
             outputRooms += '|\n'
           print '----------'
           print outputRooms
           print '----------'
           
        state = oracle(state, rooms)
    print"All room are clean now. \n There are ", sucks, "sucks, ", unsucks, "unsucks, ", bumps, "bumps, ", moves, "moves"

main()    
    
