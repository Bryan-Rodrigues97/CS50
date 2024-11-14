"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    
    x_count = sum(map(lambda line: line.count(X), board))
    o_count = sum(map(lambda line: line.count(O), board))
    
    if x_count <= o_count:
        return X
    else:
        return O

def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """ 
    action_set = set()

    for line in range(3):
        for column in range(3):
            if board[line][column] == EMPTY:
                action_set.add((line,column))

    return action_set


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    line = action[0]
    col = action[1]
    result_board = copy.deepcopy(board)

    if result_board[line][col] != EMPTY:
        raise ValueError
    
    result_board[line][col] = player(board)
    return result_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for line in board:
        if line[0] == line[1] == line[2] and line[0] != EMPTY:
            return line[0]
    
    for column in range(3):
        if board[0][column] == board[1][column] == board[2][column] and board[0][column] != EMPTY:
            return board[0][column]
    
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != EMPTY:
        return board[0][0]
    
    if board[2][0] == board[1][1] == board[0][2] and board[2][0] != EMPTY:
        return board[2][0]
    
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    empty_count = sum(map(lambda line: line.count(EMPTY), board))

    if empty_count == 0:
        return True
    
    if winner(board) != None:
        return True
        
    return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    game_winner = winner(board)

    if game_winner == X:
        return 1
    elif game_winner == O:
        return -1
    else:
        return 0

def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None
    
    best_action = None
    best_value = -math.inf if player(board) == X else math.inf

    for action in actions(board):
        if player(board) == X:
            value = min_value(result(board, action))
            if value > best_value:
                best_value = value
                best_action = action
        else:
            value = max_value(result(board, action))
            if value < best_value:
                best_value = value
                best_action = action

    return best_action


def max_value(board):
    if terminal(board):
        return utility(board)
    
    v = -math.inf
    for action in actions(board):
        v = max(v, min_value(result(board, action)))
    return v

def min_value(board):
    if terminal(board):
        return utility(board)
    
    v = math.inf
    for action in actions(board):
        v = min(v, max_value(result(board, action)))
    return v