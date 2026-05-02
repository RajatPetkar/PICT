#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;
    vector<pair<int,int>> adj[5];

    // u -> v (weight)
    adj[0].push_back({1,2});
    adj[0].push_back({2,4});
    adj[1].push_back({2,1});
    adj[1].push_back({3,7});
    adj[2].push_back({4,3});

    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,0});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(auto x : adj[u]) {
            int v = x.first, w = x.second;

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for(int i = 0; i < n; i++)
        cout << dist[i] << " ";
}
