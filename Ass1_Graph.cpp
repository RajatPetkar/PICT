#include <bits/stdc++.h>
using namespace std;

class Graph {
    map<string, vector<string>> adj;

public:
    // 1. Add edge (undirected)
    void addEdge(string u, string v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 2. Display adjacency list
    void display() {
        for (auto i : adj) {
            cout << i.first << " -> ";
            for (auto j : i.second)
                cout << j << " ";
            cout << endl;
        }
    }

    // 3. BFS
    void BFS(string start) {
        queue<string> q;
        map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string node = q.front();
            q.pop();
            cout << node << " ";

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // 4. DFS
    void DFS(string start) {
        stack<string> st;
        map<string, bool> visited;

        st.push(start);

        while (!st.empty()) {
            string node = st.top();
            st.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    st.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // 5. Degree
    void degree() {
        for (auto i : adj) {
            cout << i.first << " -> Degree: " << i.second.size() << endl;
        }
    }

    // 6. Check connectivity using BFS
    bool isConnected() {
        map<string, bool> visited;
        queue<string> q;

        string start = adj.begin()->first;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string node = q.front();
            q.pop();

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // check if all visited
        for (auto i : adj) {
            if (!visited[i.first])
                return false;
        }
        return true;
    }
};

int main() {
    Graph g;

    // Map around your college
    g.addEdge("Katraj", "PICT");
    g.addEdge("Bharti", "Katraj");
    g.addEdge("Bharti", "PICT");
    g.addEdge("Katraj", "SKNCOE");
    g.addEdge("PICT", "SKNCOE");
    g.addEdge("SKNCOE", "Temple");
    g.addEdge("Temple", "Katraj");
    g.addEdge("Temple", "Kondhwa");

    cout << "Adjacency List:\n";
    g.display();

    cout << "\nBFS: ";
    g.BFS("Katraj");

    cout << "DFS: ";
    g.DFS("Katraj");

    cout << "\nDegrees:\n";
    g.degree();

    cout << "\nConnected: ";
    cout << (g.isConnected() ? "Yes" : "No") << endl;

    return 0;
}
