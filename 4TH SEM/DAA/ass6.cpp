#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void dfs(const string& node, unordered_map<string, vector<string>>& graph, unordered_set<string>& visited) {
    if (visited.find(node) != visited.end()) return; 
    visited.insert(node);
    cout << node << " "; 

    
    for (const string& neighbor : graph[node]) {
        dfs(neighbor, graph, visited);
    }
}


void bfs(const string& start, unordered_map<string, vector<string>>& graph) {
    unordered_set<string> visited;
    queue<string> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        string node = q.front();
        q.pop();
        cout << node << " "; 

        
        for (const string& neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}

int main() {
    unordered_map<string, vector<string>> graph;
    int numNodes, numEdges;

   
    cout << "Enter the number of landmarks: ";
    cin >> numNodes;

    
    vector<string> landmarks(numNodes);
    cout << "Enter the names of the landmarks:\n";
    for (int i = 0; i < numNodes; ++i) {
        cin >> landmarks[i];
    }

    
    cout << "Enter the number of connections: ";
    cin >> numEdges;

   
    cout << "Enter the connections (format: Landmark1 Landmark2):\n";
    for (int i = 0; i < numEdges; ++i) {
        string u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    
    string startNode;
    cout << "Enter the starting landmark for DFS and BFS: ";
    cin >> startNode;

    
    cout << "DFS Traversal: ";
    unordered_set<string> visited;
    dfs(startNode, graph, visited);
    cout << endl;

  
    cout << "BFS Traversal: ";
    bfs(startNode, graph);
    cout << endl;

    return 0;
}
