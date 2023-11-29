#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 3;

// Function to print the Tic-Tac-Toe board
void printBoard(const vector<vector<char>> &board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if the current player wins
bool isWinner(const vector<vector<char>> &board, char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the board is full
bool isBoardFull(const vector<vector<char>> &board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function to evaluate the score of the board for the minimax algorithm
int evaluateBoard(const vector<vector<char>> &board) {
    if (isWinner(board, 'X'))
        return 1;
    else if (isWinner(board, 'O'))
        return -1;
    else
        return 0;
}

// Function implementing the Minimax algorithm
int minimax(vector<vector<char>> &board, int depth, bool isMaximizing) {
    int score = evaluateBoard(board);

    if (score == 1 || score == -1)
        return score;

    if (isBoardFull(board))
        return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = max(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = min(best, minimax(board, depth + 1, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the AI using Minimax
void findBestMove(vector<vector<char>> &board) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestMove.first][bestMove.second] = 'X';
}

int main() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, ' '));

    int currentPlayer = 1; // 1 for human, 2 for AI

    while (true) {
        printBoard(board);

        if (currentPlayer == 1) {
            // Human's turn
            int row, col;
            cout << "Enter row and column (1-3) for your move: ";
            cin >> row >> col;

            if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[row - 1][col - 1] == ' ') {
                board[row - 1][col - 1] = 'O';
                currentPlayer = 2; // Switch to AI's turn
            } else {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        } else {
            // AI's turn
            findBestMove(board);
            currentPlayer = 1; // Switch to human's turn
        }

        // Check if the game is over
        if (isWinner(board, 'O')) {
            printBoard(board);
            cout << "Congratulations! You win!\n";
            break;
        } else if (isWinner(board, 'X')) {
            printBoard(board);
            cout << "AI wins! Better luck next time.\n";
            break;
        } else if (isBoardFull(board)) {
            printBoard(board);
            cout << "It's a tie!\n";
            break;
        }
    }

    return 0;
}
