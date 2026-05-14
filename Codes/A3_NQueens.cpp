// Assignment 3: N-Queens using Backtracking
// No global variables | STL friendly | Parameter passing style
#include<iostream>
#include<vector>
using namespace std;

bool isSafe(int row, int col, vector<int>& board) {
    for(int i = 0; i < row; i++) {
        if(board[i] == col) return false;                      // same column
        if(abs(board[i] - col) == abs(i - row)) return false;  // diagonal
    }
    return true;
}

void printBoard(vector<int>& board, int n, int& count) {
    cout << "Solution " << ++count << ":\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void solve(int row, int n, vector<int>& board, int& count) {
    if(row == n) {
        printBoard(board, n, count);
        return;
    }
    for(int col = 0; col < n; col++) {
        if(isSafe(row, col, board)) {
            board[row] = col;        // place queen
            solve(row + 1, n, board, count); // recurse
            board[row] = -1;         // backtrack
        }
    }
}

int main() {
    int n;
    cout << "Enter N: ";
    cin >> n;

    vector<int> board(n, -1);
    int count = 0;

    solve(0, n, board, count);

    if(count == 0)
        cout << "No solution exists.\n";
    else
        cout << "Total solutions: " << count << "\n";

    return 0;
}

/*
N=4 -> 2 solutions
N=8 -> 92 solutions
*/
