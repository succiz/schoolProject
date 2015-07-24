#--coding: utf8 --

import os
import sys
import string
import time
from collections import deque

class Node:
     def __init__(self):
         self.x = 0
         self.y = 0
         self.position = []
         self.father = []
         self.path_cost = 0
         self.direction = 0
         self.father_direction = 0

     def set_direction(self, direction):
         self.direction = direction
##         self.father_direction = father_direction
     def set_position(self, position):
         self.position = position
         self.x, self.y = position
         
     def set_father(self, father):
         self.father = father

     def set_path_cost(self, cost):
          self.path_cost = cost


        
def read_from_file(filename):
        
        f = open(filename)
        lines = f.readlines()
        lines = [i.strip('() \n') for i in lines]
        print lines
        row = list([int(x) for x in lines[1].split()])[0]
        col = list([int(x) for x in lines[1].split()])[1]
        start = list([int(x)+1 for x in lines[2].split(",")])
        end = list([int(x)+1 for x in lines[3].split(",")])

        a = lines.index('BEGIN_OBSTACLES')
        b = lines.index('END_OBSTACLES')
        obstacles = []
        for i in range(a+1,b):
            obstacles.append(lines[i].split(','))
        a = lines.index('BEGIN_SEARCH_ALGS')
        temps = lines[a+1:-1]
        algs = []
        for i in range(len(temps)):
            s = temps[i]
            algs.append(s.split())

        walls = [[0 for i in range(col+2)] for j in range(row+2)]

        for i in range(row+2):
             walls[i][0] = 99
             walls[i][col+1] = 99
        for i in range(col+2):
             walls[0][i] = 99
             walls[row+1][i] = 99
        for i in range(len(obstacles)):
             walls[int(obstacles[i][0])+1][int(obstacles[i][1])+1] = 99

        return start, end, algs, walls

         
def generate_algs(start, end, algs, walls):
     node = Node()
     
     f = open('sample.txt', 'r+')
     
     for algorithem in algs:
            if algorithem[0] == 'BFS':
                t0 = time.clock()
                is_find,node, explored = BFS(start, end, walls)
                t1 = time.clock()
                f.write('Search Method: Breadth First Search\n')
                f.write('Nodes Explored: ')
                f.write(str(len(explored)))
                f.write('\n')
##                f.close()
##                print 'Search Method: Breadth First Search'
##                print 'Nodes Explored: ', len(explored)
##                qwe = f.read()
##                f.close()
##                print qwe
                if is_find == -1:
##                     print 'Cannot solve it!'
                     f.write('Cannot solve it!')
                else:
##                     print 'Solution Length: ', len(node.father)/2
                     f.write('Solution Length: ')
                     f.write(str(len(node.father)/2))
##                     f.close()
##                     f1 = open('sample.txt')
##                     ere = f1.read()
##                     f1.close()
##                     print ere
                     path = node.father+node.position
                     sol_path = []
                     for i in range(0,len(path),2):
                          sol_path.append((path[i]-1,path[i+1]-1))
                     f.write('\nSolution Path: ')
                     f.write(str(sol_path).strip('[]'))
                     f.write('\nSolution Time: ')
                     print time.time(), t0
                     f.write(str(t1-t0))
##                     print 'Solution Path: ', str(sol_path).strip('[]')
##                     print 'Solution Time: ', time.time()-t0
            elif algorithem[0] == 'DFS':
                t0 = time.time()
                is_find,node, explored = DFS(start, end, walls)
                print 'Search Method: Depth First Search'
                print 'Nodes Explored: ', len(explored)
                if is_find == -1:
                     print 'Cannot solve it!'
                else:
                     print 'Solution Length: ', len(node.father)/2
                     path = node.father+node.position
                     sol_path = []
                     for i in range(0,len(path),2):
                          sol_path.append((path[i]-1,path[i+1]-1))
                     print 'Solution Path: ', str(sol_path).strip('[]')
                     print 'Solution Time: ', time.time()-t0
            elif algorithem[0] == 'UCS':
                t0 = time.time()
                is_find,node, explored = UCS(start, end, walls)
                print 'Search Method: Uniform Cost Search'
                print 'Nodes Explored: ', len(explored)
                if is_find == -1:
                     print 'Cannot solve it!'
                else:
                     print 'Solution Length: ', len(node.father)/2
                     path = node.father+node.position
                     sol_path = []
                     for i in range(0,len(path),2):
                          sol_path.append((path[i]-1,path[i+1]-1))
                     print 'Solution Path: ', str(sol_path).strip('[]')
               
                     print 'Solution Time: ', time.time()-t0
            elif algorithem[0] == 'GBFS':
                t0 = time.time()
                is_find,node, explored = GBFS(start, end, walls)
                print 'Search Method: Greedy Best-First Search'
                print 'Nodes Explored: ', len(explored)
                if is_find == -1:
                     print 'Cannot solve it!'
                else:
                     print 'Solution Length: ', len(node.father)/2
                     path = node.father+node.position
                     sol_path = []
                     for i in range(0,len(path),2):
                          sol_path.append((path[i]-1,path[i+1]-1))
                     print 'Solution Path: ', str(sol_path).strip('[]')
               
                     print 'Solution Time: ', time.time()-t0
            elif algorithem[0] == 'ASTAR':
                t0 = time.time()
                is_find,node, explored = ASTAR(start, end, walls)
                t1 = time.time()
                print 'Search Method: A Star Search'
                print 'Nodes Explored: ', len(explored)
                if is_find == -1:
                     print 'Cannot solve it!'
                else:
                     print 'Solution Length: ', len(node.father)/2
                     path = node.father+node.position
                     sol_path = []
                     for i in range(0,len(path),2):
                          sol_path.append((path[i]-1,path[i+1]-1))
                     print 'Solution Path: ', str(sol_path).strip('[]')
                     print 'Solution Time: ', time.time()-t0
            else:
                print 'error!'
         
def BFS(start, end, walls):
     is_find = 0
     node = Node()
     node.set_position(start)
     explored = []
     q = deque()
     
     if node.position == end:
            is_find = 1
            return is_find, node, explored
          
     q.append(node)
     
     while (is_find == 0):
            if not q:
                 is_find = -1
                 return is_find, node, explored
            else:
                node = q.popleft()
                [x, y] = node.position
                explored.append([x,y])
               
                children = find_children(x,y,node,walls)
                
                for child in children:
                    if child.position not in explored:
                         positions = [element.position for element in q]
                         if child.position not in positions:
                              if child.position != end:
                                  q.append(child)
                              else:
                                  is_find = 1
                                  return is_find, child, explored
def DFS(start, end, walls):
     is_find = 0
     node = Node()
     node.set_position(start)
     explored = []
     q = deque()
     
     if node.position == end:
            is_find = 1
            return is_find, node, explored
          
     q.append(node)
     
     while (is_find == 0):
            if not q:
                 is_find = -1
                 return is_find, node, explored
            else:
                node = q.popleft()
                [x, y] = node.position
                explored.append([x,y])
               
                children = find_children(x,y,node,walls)
                
                for child in children:
                    if child.position not in explored:
                         positions = [element.position for element in q]
                         if child.position not in positions:
                              if child.position != end:
                                  q.appendleft(child)
                              else:
                                  is_find = 1
                                  return is_find, child, explored

def UCS(start, end, walls):
     is_find = 0
     node = Node()
     node.set_position(start)
     explored = []
     q = []

     q.append(node)    
     while is_find == 0:
          if not q:
               is_find = -1
               return is_find, node, explored

          node = q[0]
          for everynode in q:
               if everynode.path_cost < node.path_cost:
                    node = everynode
          q.remove(node)
          
          if node.position == end:
               is_find = 1
               return is_find, node, explored    

          [x, y] = node.position
          cost = node.path_cost
          explored.append([x,y])               
          children = find_children(x,y,node,walls)
          
          for child in children:
               
               if child.direction == node.direction or node.direction == 0:
                    child.set_path_cost(cost+1)
               elif node.direction == node.direction+1:
                    child.set_path_cost(cost+2)
               else:
                    child.set_path_cost(cost+3)
                    
               if child.position not in explored:
                    positions = [element.position for element in q]
                    if child.position not in positions:
                         q.append(child)
                    else:
                         index = positions.index(child.position)
                         if child.path_cost < q[index].path_cost:
                              q.pop(index)
                              q.append(child)

def GBFS(start, end, walls):
     is_find = 0
     node = Node()
     cur_node = Node()
     node.set_position(start)
     explored = []
     q = deque()
     
     q.append(node)
     
     while is_find == 0:
          node = q.popleft()
          [x, y] = node.position
          if node.position == end:
               is_find = 1
               return is_find, node, explored
          shortest = abs(end[0] - x)+abs(end[1] - y)
          
          children = find_children(x,y,node,walls)
          for child in children:
              temp = abs(end[0] - child.x)+abs(end[1] - child.y)
              if temp < shortest:
                   cur_node = child
                   shortest = temp
          if shortest == abs(end[0] - node.x)+abs(end[1] - node.y):
              is_find = -1
              return is_find, node, explored
          explored.append(node)
          q.append(cur_node)
##                              
##def GBFS(start, end, walls):
##     is_find = 0
##     node = Node()
##     cur_node = Node()
##     node.set_position(start)
##     explored = []
##     q = []
##     
##     q.append(node)
##     
##     while is_find == 0:
##          if not q:
##                 is_find = -1
##                 return is_find, node, explored
##               
##          node = q[0]
##          [x, y] = node.position
##          shortest = abs(end[0] - x)+abs(end[1] - y)
##          
##          for everynode in q:
##              [r, c] = everynode.position
##              temp = abs(end[0] - r)+abs(end[1] - c)
##              if temp < shortest:
##                  node = everynode
##                  shortest = temp        
##          q.remove(node)
##          
##          if node.position == end:
##               is_find = 1
##               return is_find, node, explored
##          
##          [x, y] = node.position
##          shortest = abs(end[0] - x)+abs(end[1] - y)
##          
##          children = find_children(x,y,node,walls)
##          
##          for child in children:
##               if child not in explored:
##                    q.append(child)
##
##          explored.append(node)
##          print explored
          
def ASTAR(start, end, walls):
     
     is_find = 0
     node = Node()
     cur_node = Node()
     node.set_position(start)
     explored = []
     q = []
     
     q.append(node)
     
     while is_find == 0:
          if not q:
                 is_find = -1
                 return is_find, node, explored
               
          node = q[0]
          
          for everynode in q:
              if everynode.path_cost < node.path_cost:
                  node = everynode
       
          q.remove(node)
          explored.append(node.position)

          if node.position == end:
               is_find = 1
               return is_find, node, explored
          
          [x, y] = node.position
          shortest = abs(end[0] - x)+abs(end[1] - y)
          
          children = find_children(x,y,node,walls)
          
          for child in children:
               [cr, cc] = child.position
               if child.position not in explored:
                    cost = abs(end[0] - cr)+abs(end[1] - cc)+abs(start[0] - cr)+abs(start[1] - cc)
                    child.set_path_cost(cost)
                    if child not in q:
                         q.append(child)

          
def find_children(x, y, node, walls):
     temp_children = []
     if walls[x-1][y] != 99:
          temp_node = Node()
          temp_node.set_position([x-1,y])
          temp_node.set_father(node.father+[x,y])
          temp_node.set_direction(100)
          temp_children.append(temp_node)
     if walls[x+1][y] != 99:
          temp_node = Node()
          temp_node.set_position([x+1,y])
          temp_node.set_father(node.father+[x,y])
          temp_node.set_direction(101)
          temp_children.append(temp_node)
     if walls[x][y-1] != 99:
          temp_node = Node()
          temp_node.set_position([x,y-1])
          temp_node.set_father(node.father+[x,y])
          temp_node.set_direction(200)
          temp_children.append(temp_node)
     if walls[x][y+1] != 99:
          temp_node = Node()
          temp_node.set_position([x,y+1])
          temp_node.set_father(node.father+[x,y])
          temp_node.set_direction(201)
          temp_children.append(temp_node)

     return temp_children


     

##filename = sys.argv[1]
start, end, algs, walls = read_from_file('C:\Users\yanxin^^\Desktop\p2\one.rwf.txt')
generate_algs(start, end, algs, walls)

