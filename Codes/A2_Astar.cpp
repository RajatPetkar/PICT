// Assignment 2: A* Algorithm - 8 Puzzle Problem
// No global variables | STL friendly | Parameter passing style
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

struct State {
    vector<vector<int>> board;
    int g, h, f;
    int px, py; // blank (0) position
};

int heuristic(vector<vector<int>>& board) {
    int dist = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) {
            int val = board[i][j];
            if(val != 0) {
                int ti = (val - 1) / 3;
                int tj = (val - 1) % 3;
                dist += abs(i - ti) + abs(j - tj);
            }
        }
    return dist;
}

bool isGoal(vector<vector<int>>& board) {
    int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] != goal[i][j]) return false;
    return true;
}

void printBoard(vector<vector<int>>& board) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
    cout << "-------\n";
}

void astar(vector<vector<int>>& startBoard) {
    vector<State> open;

    // Find blank position
    int px = 0, py = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(startBoard[i][j] == 0) { px = i; py = j; }

    State s;
    s.board = startBoard;
    s.g = 0;
    s.h = heuristic(startBoard);
    s.f = s.h;
    s.px = px; s.py = py;
    open.push_back(s);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int step = 0;

    while(!open.empty()) {
        // Find min f in open list
        int minIdx = 0;
        for(int i = 1; i < (int)open.size(); i++)
            if(open[i].f < open[minIdx].f) minIdx = i;

        State cur = open[minIdx];
        open.erase(open.begin() + minIdx);

        cout << "Step " << step++ << " (g=" << cur.g << ", h=" << cur.h << "):\n";
        printBoard(cur.board);

        if(isGoal(cur.board)) {
            cout << "Goal Reached in " << cur.g << " moves!\n";
            return;
        }

        if(step > 25) { cout << "Too many steps. Try easier input.\n"; return; }

        for(int d = 0; d < 4; d++) {
            int nx = cur.px + dx[d];
            int ny = cur.py + dy[d];
            if(nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;

            State next;
            next.board = cur.board; // copy board
            swap(next.board[cur.px][cur.py], next.board[nx][ny]);
            next.px = nx; next.py = ny;
            next.g = cur.g + 1;
            next.h = heuristic(next.board);
            next.f = next.g + next.h;
            open.push_back(next);
        }
    }
    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> board(3, vector<int>(3));
    cout << "Enter 3x3 puzzle (0 = blank):\n";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            cin >> board[i][j];

    cout << "\nInitial Board:\n";
    printBoard(board);
    cout << "Solving...\n\n";

    astar(board);
    return 0;
}

/*
Sample Input (2 moves from goal):
1 2 3
4 5 6
0 7 8
*/
