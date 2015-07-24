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

##define functions:
#####################################################################
##set_blocks fuction
##
##This fucntion hardcode 10 blocks in 100 rooms, meanwhile all the
##blocks and rooms are reachable
##
##Return: 10 blocks
##
##Reference Parameters: rooms
#####################################################################
def set_blocks(rooms):
    (rooms[0][0], rooms[1][2], rooms[2][7], rooms[3][4], rooms[5][1], rooms[6][5], rooms[7][5], rooms[8][7], rooms[9][0], rooms[9][5]) = (-1,-1,-1,-1,-1,-1,-1,-1,-1,-1)
    return rooms

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
##Return: x, y, temp
##
##Reference Parameters: x, y, direction, temp
#####################################################################   
def action(x, y, direction, temp):
    if direction == 'left':
        temp = y
        y = y - 1
    elif direction == 'right':
        temp = y
        y = y + 1
    elif direction == 'up':
        temp = x
        x = x - 1
    elif direction == 'down':
        temp = x
        x = x + 1
    return x, y, temp
       
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
    
    temp = 0
    x, y, temp = action(x, y, direction, temp)
    if (direction == 'up' or direction == 'down') and (x not in range(10) or rooms[x][y] == -1):
            x = temp
            bumps = bumps + 1          
    elif (direction == 'left' or direction == 'right') and (y not in range(10) or rooms[x][y] == -1):
            y = temp
            bumps = bumps + 1
    else:
        moves = moves+1
    return x, y , sucks, bumps, moves, rooms

def main():
    rooms = [[0 for i in range(10)] for j in range(10)]
    rooms = set_blocks(rooms)

    print "This is the 10x10 environment with 10 blocks:(x=blocks,#=dirty rooms,@=robot)"
##    print " -- -- -- -- -- -- -- -- -- --"
##    for i in range(10):
##        for j in range (10):
##            if rooms[i][j] == -1:
##                print "|X",
##            else:
##                print "|O",
##        print "|"
##        print " -- -- -- -- -- -- -- -- -- --"   
    x = random.randint(0,9)
    y = random.randint(0,9)
    while rooms[x][y] == -1:
        x = random.randint(0,9)
        y = random.randint(0,9)
    sucks = 0
    bumps = 0
    moves = 0
    state = 0
    while state == 0:
##        x, y , sucks, bumps, moves = agent(x, y, sucks, bumps, moves, rooms)

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
    print"All room are clean now. \n There are ", sucks, "sucks, ", bumps, "bumps, ", moves, "moves"

main()    
    
    

