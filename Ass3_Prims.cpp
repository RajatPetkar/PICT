#include <iostream>
#include <vector>
#include <queue>
#include<bits/stdc++.h>
using namespace std;

#define MAX 100

typedef pair<int, int> pii; // (weight, vertex)

int main() {
    int n, e;
    cout << "Enter number of buildings: ";
    cin >> n;

    cout << "Enter number of connections: ";
    cin >> e;

    vector<pii> adj[MAX];

    cout << "Enter connections (u v cost):\n";
    for(int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({w, v});
        adj[v].push_back({w, u}); // undirected graph
    }

    vector<int> key(n, INT_MAX);   // Minimum cost to connect
    vector<bool> inMST(n, false);  // Track MST inclusion

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start from node 0
    key[0] = 0;
    pq.push({0, 0});

    int totalCost = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if(inMST[u]) continue;

        inMST[u] = true;
        totalCost += weight;

        for(auto edge : adj[u]) {
            int v = edge.second;
            int w = edge.first;

            if(!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w, v});
            }
        }
    }

    cout << "\nMinimum Cost = " << totalCost << endl;

    return 0;
}