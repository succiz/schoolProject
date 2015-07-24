#--coding: utf8 --

import os
import sys
import string
from collections import deque

class State:#?
     def __init__(self):
         self.father = []
         self.position = []
         self.path_cost = 0
         
##     def set_value(self, value):
##         self.value = value

     def set_direction(self, direction):
         self.direction = direction

     def set_position(self, positon):
         self.position = position
         
     def set_father(self, father):
         self.father.append(father)
         
     def get_value(self):
         return self.value

     def get_position(self):
         return self.position
         
         
     def get_father(father):
         return self.father

class G:
    
    def __init__(self):
        self.row = 0
        self.col = 0
        self.start = []
        self.end = []
        self.obstacles = []
        self.algs = []
        self.walls = []
        
    def read_from_file(self, filename):
        
        f = open(filename)
        lines = f.readlines()
        self.row = list([int(x) for x in lines[1].split()])[0]
        self.col = list([int(x) for x in lines[1].split()])[1]
        self.start = list([int(x) for x in lines[2].strip()[1:-1].split(",")])
        self.end = list([int(x) for x in lines[3].strip()[1:-1].split(",")])
        a = lines.index('BEGIN_OBSTACLES')
        b = lines.index('END_OBSTACLES')
        obstacles = lines[a+1:b-1]
        self.obstacles = list([int(x)+1 for x in obstacles[i in range(len(obstacles))].strip()[1:-1].split(",")])
        a = lines.index('BEGIN_SEARCH_ALGS')
        b = lines.index('END_SEARCH_ALGS')
        temps = lines[a+1:b-1]
        for i in range(len(temps)):
            s = temps[i]
            self.algs[i] = s.split()
            
     def set_walls(self):
         for i in range(0,row+1):
             self.walls.append([i,0])
             self.walls.append([i,col+1])
         for i in range(0,col+1):
             self.walls.append([0,i])
             self.walls.append([row+1,i])

        print row,' ',col,' ',obstacles,' ', algs

class RobotWorld():
    
    def __init__(self):
        self.find = 0
        self.q = deque()
        self.solution = []
        self.cost = 0
        self.explored_nodes = 0
        self.node = nodes[G.start[0]][G.start[1]]
        self.start = []
        self.end = []
        self.obstacles = []
        self.algs = []
        self.walls = []
        
    def generate_nodes(self, G.row, G.col):
        for i in range(G.row+1):
            for j in range(G.col+1):
                self.nodes[i][j] = Node()
                if [i,j] in G.obstacles or [i,j] in G.walls:
                    self.nodes[i][j].set_value(99)#?
                else:
                    nodes[i][j].set_value(0)
                self.nodes[i][j].set_position([i,j])
                
    def find_children(self):
       [x, y] = self.node.get_position()
       if self.nodes[x-1][y] not 99:
           q.append(self.nodes[x-1][y])
           self.nodes[x-1][y].set_father([x,y])
       if self.nodes[x+1][y] not 99:
           q.append(self.nodes[x-1][y])
           self.nodes[x+1][y].set_father([x,y])
       if self.nodes[x][y-1] not 99:
           q.append(self.nodes[x-1][y])
           self.nodes[x][y-1].set_father([x,y])
       if self.nodes[x][y+1] not 99:
           q.append(self.nodes[x-1][y])
           self.nodes[x][y+1].set_father([x,y])
        
    
##
##    def generate_algs(G.algs):
##        for i in range(len(algs)):
##            if len(algs[i]) == 'BFS':
##                BFS()
##            elif len(algs[i]) == 'BFS':
##                DFS()
##            elif len(algs[i]) == 'BFS':
##                UCS()
##            elif len(algs[i]) == 'BFS':
##                GBFS()
##            elif len(algs[i]) == 'BFS':
##                ASTAR()
##            else:
##                print 'error!'

    def BFS(self, G.end):
        
        if self.node.get_position() == G.end:
            self.find = 1
            self.solution.append(self.node)
            return self.node
          
        q.append(self.node)
        while (self.find == 0):
            if q == null:#?
                 return self.find = -1
            else:
                self.node = q.popleft()
                explored_nodes.append(self.node)
                [x, y] = self.node.get_position()
                if self.nodes[x-1][y].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x-1][y].set_father([x,y])
                if self.nodes[x+1][y].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x+1][y].set_father([x,y])
                   if self.nodes[x][y-1].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x][y-1].set_father([x,y])
                   if self.nodes[x][y+1].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x][y+1].set_father([x,y])
                for nodes in child:
                    if nodes.get_position() != G.end:
                        self.q.append(nodes)
                    else:
                        self.find = 1
                       
        def DFS(self, G.end):
        
        if self.node.get_position() == G.end:
            self.find = 1
            self.solution.append(self.node)
            return self.node
          
        q.append(self.node)
        while (self.find == 0):
            if q == null:#?
                 return self.find = -1
            else:
                self.node = q.popleft()
                explored_nodes.append(self.node)
                [x, y] = self.node.get_position()
                if self.nodes[x-1][y].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x-1][y].set_father([x,y])
                if self.nodes[x+1][y].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x+1][y].set_father([x,y])
                   if self.nodes[x][y-1].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x][y-1].set_father([x,y])
                   if self.nodes[x][y+1].get_value not 99:
                       child.append(self.nodes[x-1][y])
                       self.nodes[x][y+1].set_father([x,y])
                for nodes in child:
                    if nodes.get_position() != G.end:
                        self.q.appendleft(nodes)
                    else:
                        self.find = 1

##     procedure UniformCostSearch(Graph, root, goal)
##
##node := root, cost = 0
##frontier := priority queue containing node only
##explored := empty set
##do 
##if frontier is empty 
##return failure
##node := frontier.pop()
##if node is goal 
##return solution
##explored.add(node)
##for each of node's neighbors n 
##if n is not in explored 
##if n is not in frontier 
##frontier.add(n)
##if n is in frontier with higher cost 
##replace existing node with n
     
     def UCS(G.end):
          [x,y] = G.start
          cost = 0
          find = 0
          q.append(nodes[x][y])
          explored = []
          while find == 0:
               if q == null:#
                    return find = -1
               node = q.popleft()
               if node.get_positon() == G.end:
                    return find = 1
               explored.append(node)
               for n in node.child():
                    if n not in explored:
                         if n not in q:
                              q.append(n)
                         if n in q and
matched_indexes=[i for i, node in enumerate(q) if node.x == n.x and node.y == n.y]
for i in matched_indexes:
     q[i].cost
          
      def GBFS(G.start, G.end):
           X = G.end[0]
           Y = G.end[1]
           node = G.start
           if node == G.end:
               return find = 1
           else:
           while True:
               shortest = abs(X - node[0])+abs(Y - node[1])
               for nodes in pool:#neigbors
                    if nodes == G.end:
                         return find = 1
                    else:
                         temp = abs(X - nodes[0])+abs(Y - nodes[1])
                         if temp <= shortes:
                             shortest = temp
     
         
##filename = sys.argv[1]
read_from_file('C:\Users\yanxin^^\Documents\CS\AI\Proj2\one.rwf.txt')
        
            
