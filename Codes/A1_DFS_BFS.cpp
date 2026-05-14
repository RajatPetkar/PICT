// Assignment 1: DFS and BFS on Undirected Graph
// No global variables | STL friendly | Parameter passing style
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";
    for(int neighbor : adj[node]) {
        if(!visited[neighbor])
            dfs(neighbor, adj, visited);
    }
}

void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for(int neighbor : adj[node]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> adj(n); // adjacency list

    for(int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter edge (u v): ";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    int start;
    cout << "Enter start vertex: ";
    cin >> start;

    vector<bool> visitedDFS(n, false);
    cout << "\nDFS Traversal: ";
    dfs(start, adj, visitedDFS);

    vector<bool> visitedBFS(n, false);
    cout << "\nBFS Traversal: ";
    bfs(start, adj, visitedBFS);

    cout << endl;
    return 0;
}

/*
Sample Input:
Vertices: 5 | Edges: 4
0 1 | 0 2 | 1 3 | 1 4
Start: 0
DFS: 0 1 3 4 2
BFS: 0 1 2 3 4
*/
