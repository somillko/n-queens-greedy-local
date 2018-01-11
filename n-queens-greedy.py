import numpy as np
import random


N = 8

def h_function (board, N, location):
    count = 0

    # down & right #
    for r, c in zip(range(location[0] + 1, N, 1), range(location[1] + 1, N, 1)):
        if board[r][c] == 1:
            count += 1

    # down & left #
    for r, c in zip(range(location[0] + 1, N, 1), range(location[1] - 1, -1, -1)):
        if board[r][c] == 1:
            count += 1

    # down #
    for r in range(location[0] + 1, N):
        if board[r][location[1]] == 1:
            count += 1

    return count


def init_board(board, N, locations):

    board = np.zeros((N,N), dtype='int8')

    # Generate random locations #
    locations = np.zeros((N,), dtype='i,i')
    for r in range(N):
        locations[r] = (r, random.randint(0, N - 1))
        board[r][locations[r][1]] = 1
