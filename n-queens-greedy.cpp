/*
Author:         Michael Schmidt

Description:    Solve the N-Queens problem using greedy descent.
*/

/* Includes */
#include "globals.h"

/* Prototypes */
int get_lowest (const Board & board, const int N, Locations & minimums);
int h_function (const Board & board, const int N, const Pair & location);
bool is_solution (const Board & board, const int N ,const Locations & queens);
void print_board (const Board & board, const int N);
void init_board (Board & board, const int N, Locations & queens);
void put_lowest (Board & board, const int N, const Locations & mins, Locations & queens);
void update_board (Board & board, const int N, const Locations & queens);

//////////////
/* INT MAIN */
//////////////

int main (int argc, char * argv[]) {
    assert(argc == 3 && "Two command line arguements must be supplied for N and seed.");
    srand(atoi(argv[2]));

    /* Constants */
    const int N = atoi(argv[1]);

    /* Environment */
    Board board = nullptr;
    Locations queens;
    Locations minimums;

    /* Variables */
    int tries = N / 2;
    int curr;
    int last;

    /* Populate the board with queens in a random starting position */
    init_board(board, N, queens);

    update_board(board, N, queens);
    curr = get_lowest(board, N, minimums);

    do {
        put_lowest(board, N, minimums, queens);
        update_board(board, N, queens);

        last = curr;
        curr = get_lowest(board, N, minimums);

        if (curr >= last)
            tries--;

        /* If we can't improve after N / 2 attempts, try a new random board. */
        if (!tries) {
            init_board(board, N, queens);
            tries = N / 2;
        }

    } while (!is_solution(board, N, queens));
    print_board(board, N);

    /* Clean up */
    for (int i = 0; i < N; i++)
        delete [] board[i];
    delete [] board;

    return 0;
}

///////////////
/* FUNCTIONS */
///////////////

int h_function (const Board & board, const int N, const Pair & location) {
    int count = 0;

    /* down & right */
    for (int r = location.r + 1, c = location.c + 1; r < N && c < N; r++, c++)
           if (board[r][c] == -1)
               count++;

    /* down & left */
    for (int r = location.r + 1, c = location.c - 1; r < N && c > -1; r++, c--)
           if (board[r][c] == -1)
               count++;

    /* down */
    for (int r = location.r + 1, c = location.c; r < N; r++)
        if (board[r][c] == -1)
            count++;

    return count;
}

void update_board (Board & board, const int N, const Locations & queens) {
    int count = 0;

    /* For ever row, calculate the heuristic value as if the queen was moved
       to every sqaure in that row */
    for (int r = 0; r < N; r++) {
        board[queens[r]->r][queens[r]->c] = 0;
        for (int c = 0; c < N; c++) {
            board[r][c] = -1;
            for (int k = 0; k < N; k++)
                if (k != r)
                    count += h_function(board, N, queens[k]);
            count += h_function(board, N, Pair(r,c));
            board[r][c] = (queens[r]->r == r && queens[r]->c == c) ? -1 : count;
            count = 0;
        }
    }
}

int get_lowest (const Board & board, const int N, Locations & minimums) {
    int min = (board[0][0]) != -1 ? board[0][0] : board[0][1];
    minimums.clear();

    /* Find the minimum value on the board */
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (board[r][c] < min && board[r][c] != -1)
                min = board[r][c];

    /* Find all the mimimums values */
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (board[r][c] == min) {
                PairPtr min = new Pair(r, c);
                minimums.push_back(min);
            }

    return min;
}

void put_lowest (Board & board, const int N, const Locations & mins, Locations & queens) {
    /* Pick a random minimum location */
    int move = rand() % mins.size();
    int row = mins[move]->r;
    int col = mins[move]->c;

    /* Find the queen and replace it with an heuristic value */
    for (int c = 0; c < N; c++)
        if (board[row][c] == -1) {
            board[row][col] = -1;               // Put new queen
            queens[row]->r = row;
            queens[row]->c = col;

            board[row][c] = 0;                  // Remove old queen
            break;
        }
}

void init_board (Board & board, const int N, Locations & queens) {
    /* Create a board if it doesn't exist */
    if (!board) {
        board = new Tile*[N];
        for (int r = 0, i; r < N; r++)
            board[r] = new Tile[N];
    }

    /* Zero out old board */
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            board[r][c] = 0;

    /* Clear the queens list */
    queens.clear();

    /* Assign queens 1 per column randomly */
    for (int r = 0, i; r < N; r++) {
        int c = rand() % N;
        board[r][c] = -1;
        PairPtr queen = new Pair(r,c);
        queens.push_back(queen);
    }
}

bool is_solution (const Board & board, const int N, const Locations & queens) {
    /* Check the heuristic for each queen */
    for (int i = 0; i < N; i++)
        if (h_function(board, N, queens[i]))
            return false;

    return true;
}

void print_board (const Board & board, const int N) {
    /* Print the board: -1 are queens, everything else is blank */
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            if (board[r][c] == -1)
                cout <<"Q ";
            else
                cout << "- ";
        cout << endl;
    }
}
