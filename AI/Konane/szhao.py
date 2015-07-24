import random
import math
from updatedKonane import *

class MinimaxNode:
    """
    Black always goes first and is considered the maximizer.
    White always goes second and is considered the minimizer.
    """
    def __init__(self, state, player):
        self.state = state
        self.operator = []
        self.depth = 0
        self.player = player
        if player == 'B':
            self.op_player = 'W'
        if player == 'W':
            self.op_player = 'B'
            
    def set_depth(self, depth):
        self.depth = depth
        
    def set_operator(self, operator):
        self.operator = operator
        
class szhaoPlayer(Konane, Player):

    def __init__(self, size, depthLimit):
        Konane.__init__(self, size)
        Player.__init__(self)
        self.limit = depthLimit

    def initialize(self, side):
        """
	Initializes the player's color and name.
	"""
	self.side = side
        self.name = "MinimaxDepth" + str(self.limit) + "Zhao"

    def getMove(self, board):
        """
        Returns the chosen move based on doing an alphaBetaMinimax 
	search.
        """
        if self.openingMove(board):
            if self.side == 'B':
                return self.generateFirstMoves(board)[0]
        node = MinimaxNode(board, self.side)
        self.alphaBetaMinimax(node, -1000, 1000)
        return self.bestMove
              
        

    def staticEval(self, node):#?
        """
	Returns an estimate of the value of the state associated
	with the given node.
        """
        b_num = 0
        w_num = 0
        for i in self.board:
            if i == 'B':
                b_num = b_num + 1
            else:
                w_num = w_num + 1
        if node.player == 'B':
            differ = b_num - w_num
        else:
            differ = w_num - b_num

        if node.operator != []:
            num = differ*(math.fabs(node.operator[0]-node.operator[2]+node.operator[1]-node.operator[3]))
        else:
            num = 0
        return num
##        num = random.randrange(10)
##        return num       
        

    def successors(self, node):
        """
        Returns a list of the successor nodes for the given node.
        """
        children = []
        moves = self.generateMoves(node.state, self.side)
        #print 'moves:',moves
        for move in moves:
            state = self.nextBoard(node.state, self.side, move)
            a_node = MinimaxNode(state, self.side)
            a_node.set_depth(node.depth+1)
            if node.depth == 0:
                a_node.operator = move
            else :
                a_node.operator = move
            children.append(a_node)
        return children
        

    def alphaBetaMinimax(self, node, alpha, beta):
        """
	Returns the best score for the player associated with the 
	given node.  Also sets the instance variable bestMove to the
        move associated with the best score at the root node.
	Initialize alpha to -infinity and beta to +infinity.
        """
        
        # check if at search bound
        if node.depth == self.limit:
            return self.staticEval(node)

        # check if leaf
        children = self.successors(node)
        
        if len(children) == 0:
            if node.depth == 0:
                self.bestMove = [] 
            return self.staticEval(node)

        # initialize bestMove
        if node.depth == 0:
            self.bestMove = children[0].operator
            
        # check if there is only one option
        if len(children) == 1:
            return None

        if node.player == 'B':
            for child in children:
                result = self.alphaBetaMinimax(child, alpha, beta)
                if result > alpha:
                    alpha = result
                    if node.depth == 0:
                        self.bestMove = child.operator
                if alpha >= beta:
                    return alpha
            return alpha

        if node.player == 'W':
            for child in children:
                result = self.alphaBetaMinimax(child, alpha, beta)
                if result < beta:
                    beta = result
                    if node.depth == 0:
                        bestMove = child.operator
                if beta <= alpha:
                    return beta
            return beta


        
