#include <iostream>
#include <vector>

using namespace std;

// Function to print the chessboard
void printSolution(const vector<int>& queens) {
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if placing a queen at (row, col) is safe
bool isSafe(const vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; ++i) {
        // Check if the queen is in the same column or diagonals
        if (queens[i] == col || queens[i] - i == col - row || queens[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

// Function to solve the N-Queens problem using backtracking
void solveNQueens(vector<int>& queens, int row, int n) {
    if (row == n) {
        // All queens are placed successfully, print the solution
        printSolution(queens);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(queens, row, col)) {
            // Place the queen and move on to the next row
            queens[row] = col;
            solveNQueens(queens, row + 1, n);
            // Backtrack if the placement leads to a solution
        }
    }
}

int main() {
    int n;
    cout << "Enter the value of N for N-Queens: ";
    cin >> n;

    // Initialize a vector to store the column position of queens for each row
    vector<int> queens(n, -1);

    // Solve the N-Queens problem
    solveNQueens(queens, 0, n);

    return 0;
}
