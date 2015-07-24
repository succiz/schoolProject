#Shuyi Zhao
#COSC 5354: Artificial Intelligence
#Due: Sep 30, 2011
#Project: Vacuum Cleaner World: part 1

#All the rooms are dirty at the begainning
#All the movements are random
#Agent cannot know the state of the whole enviroment

#--coding: utf8 --
#import :
import random
import os

# global variable
direction_list = ['left','right','up','down']

##define functions:
#####################################################################
## choose_direction fuction
##
##This fucntion choose a random direction that the vacuum will go to
##
##Return: the direction it choosed
##
##Reference Parameters: NONE
#####################################################################
def choose_direction():
   return random.choice(direction_list)

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
    for i in range(10):
        for j in range(10):
            if rooms[i][j] == 0:
                return state
    state = 1
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
def is_clean(x, y, sucks, rooms):
    if rooms[x][y] == 0:
       sucks = sucks + 1
       rooms[x][y] = 1
    return sucks, rooms

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
##Return: x, y, sucks, bumps, moves
##
##Reference Parameters: x, y, sucks, bumps, moves, rooms
#####################################################################
def agent(x, y, sucks, bumps, moves, rooms):
   #percept the state
    sucks, rooms = is_clean(x, y, sucks, rooms)
    
    direction = choose_direction()
    if ((x == 0 and direction == 'up') or (x == 9 and direction == 'down') or
        (y == 0 and direction == 'left') or (y == 9 and direction == 'right')):
       bumps = bumps + 1
    else:
        moves = moves+1
        x, y = action(x, y, direction)
    return x, y , sucks, bumps, moves, rooms

def main():
    rooms = [[0 for i in range(10)] for j in range(10)]
    x = 0
    y = 0
    sucks = 0
    bumps = 0
    moves = 0
    state = 0

    print "This is the 10x10 environment with 10 blocks:(x=blocks,#=dirty rooms,@=robot)"
    
    while state == 0:
        if moves%100 == 0:
           #print rooms
           displayRooms = [['#' if rooms[i][j] == 0 else 'x' if rooms[i][j] == -1 else ' ' for i in range(10)] for j in range(10)]
           displayRooms[x][y] = '@'
           outputRooms = ''
           for i in range(10):
             for j in range(10):
                outputRooms += str(displayRooms[i][j])
             outputRooms += '|\n'
           print '----------'
           print outputRooms
           print '----------'
       
        x, y , sucks, bumps, moves, rooms = agent(x, y, sucks, bumps, moves, rooms)

        state = oracle(state, rooms)
    print"All room are clean now. \nThere are ", sucks, "sucks, ", bumps, "bumps, ", moves, "moves"

main()    
    
    
