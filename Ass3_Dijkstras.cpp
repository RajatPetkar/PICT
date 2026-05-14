#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<pair<int,int>> adj[n];
    // Input graph
    cout << "\nEnter edges and weights:\n";
    cout << "Format: source destination weight\n";
    for(int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // For undirected graph use this also:
        // adj[v].push_back({u, w});
    }
    // Display graph
    cout << "\nAdjacency List:\n";
    for(int i = 0; i < n; i++) {
        cout << i << " -> ";
        for(auto x : adj[i]) {
            cout << "(" << x.first
                 << "," << x.second << ") ";
        }
        cout << endl;
    }

    int source;
    cout << "\nEnter source vertex: ";
    cin >> source;

    // Dijkstra
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0, source});
    while(!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        for(auto x : adj[u]) {

            int v = x.first;
            int w = x.second;

            if(dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;

                pq.push({dist[v], v});
            }
        }
    }

    // Output shortest distances
    cout << "\nShortest Distances:\n";
    for(int i = 0; i < n; i++) {
        cout << "Distance from "
             << source
             << " to "
             << i
             << " = ";
        if(dist[i] == INT_MAX)
            cout << "INF";
        else
          cout << dist[i];
        cout << endl;
    }
    return 0;
}
