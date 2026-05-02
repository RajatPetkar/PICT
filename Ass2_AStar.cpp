#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class Node {
public:
    int state[3][3];
    int g, h;
    int x, y; // blank position
    Node* parent;
    
    Node(int s[3][3], int cost, int blankX, int blankY, Node* p, int goal[3][3]) {
        // Copy state
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                state[i][j] = s[i][j];
            }
        }
        g = cost;
        x = blankX;
        y = blankY;
        parent = p;
        h = hammingHeuristic(state, goal);
    }
    
    int f() const {
        return g + h;
    }
    
    // Hamming heuristic - count misplaced tiles
    static int hammingHeuristic(int curr[3][3], int goal[3][3]) {
        int misplaced = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(curr[i][j] != 0 && curr[i][j] != goal[i][j]) {
                    misplaced++;
                }
            }
        }
        return misplaced;
    }
    
    // Create unique key for state
    string key() const {
        string k = "";
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                k += (char)('0' + state[i][j]);
                k += ",";
            }
        }
        return k;
    }
};

// Comparator for priority queue (min heap based on f value)
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

int goal[3][3];
int dx[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
int dy[] = {0, 0, -1, 1};

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < 3 && y < 3;
}

void printState(int state[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(state[i][j] == 0)
                cout << "_ ";
            else
                cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve(int start[3][3], int sx, int sy) {
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    set<string> visited;
    
    Node* startNode = new Node(start, 0, sx, sy, NULL, goal);
    pq.push(startNode);
    
    int iterations = 0;
    
    while(!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();
        iterations++;
        
        // Goal reached when h = 0
        if(curr->h == 0) {
            cout << "GOAL REACHED!" << endl;
            cout << "Total Moves: " << curr->g << endl;
            cout << "Total Iterations: " << iterations << endl;
            cout << "\nSOLUTION PATH:\n" << endl;
            
            // Reconstruct path
            vector<Node*> path;
            Node* temp = curr;
            while(temp != NULL) {
                path.push_back(temp);
                temp = temp->parent;
            }
            reverse(path.begin(), path.end());
            
            for(int i = 0; i < path.size(); i++) {
                cout << "Step " << i << ":" << endl;
                printState(path[i]->state);
            }
            
            return;
        }
        
        visited.insert(curr->key());
        
        // Try all 4 directions
        for(int i = 0; i < 4; i++) {
            int nx = curr->x + dx[i];
            int ny = curr->y + dy[i];
            
            if(valid(nx, ny)) {
                // Create new state
                int newState[3][3];
                for(int r = 0; r < 3; r++) {
                    for(int c = 0; c < 3; c++) {
                        newState[r][c] = curr->state[r][c];
                    }
                }
                
                // Swap blank with adjacent tile
                newState[curr->x][curr->y] = newState[nx][ny];
                newState[nx][ny] = 0;
                
                Node* child = new Node(newState, curr->g + 1, nx, ny, curr, goal);
                
                if(visited.find(child->key()) == visited.end()) {
                    pq.push(child);
                }
            }
        }
    }
    
    cout << "No solution found!" << endl;
}

int main() {
    int start[3][3];
    int zx = 0, zy = 0;
    
    cout << "Enter the initial state (use 0 for blank):" << endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> start[i][j];
            if(start[i][j] == 0) {
                zx = i;
                zy = j;
            }
        }
    }
    
    cout << "Enter the goal state:" << endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> goal[i][j];
        }
    }
    
    cout << "\n===== STARTING A* SEARCH =====" << endl;
    solve(start, zx, zy);
    
    return 0;
}
