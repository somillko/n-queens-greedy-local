import numpy as np
import random


N = 8

def init_board(board, N, locations):

    board = np.zeros((n,n), dtype='int8')

    # Generate random locations #
    locations = np.zeros((n,), dtype='i,i')
    for c in range(n):
        locations[c] = (c, random.randint(0, n))
