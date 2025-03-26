#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

struct Node {
    string data;
    Node* next;
    Node(const string& data) : data(data), next(nullptr) {}
};


class Graph {
public:
    unordered_map<string, Node*> adjList;

    void addEdge(const string& u, const string& v) {
        Node* newNodeU = new Node(v);
        newNodeU->next = adjList[u];
        adjList[u] = newNodeU;

        Node* newNodeV = new Node(u);
        newNodeV->next = adjList[v];
        adjList[v] = newNodeV;
    }

    void dfs(const string& node, unordered_set<string>& visited) {
        if (visited.find(node) != visited.end()) return;
        visited.insert(node);
        cout << node << " ";

        Node* current = adjList[node];
        while (current) {
            dfs(current->data, visited);
            current = current->next;
        }
    }


    void bfs(const string& start) {
        unordered_set<string> visited;
        queue<string> q;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string node = q.front();
            q.pop();
            cout << node << " ";

            Node* current = adjList[node];
            while (current) {
                if (visited.find(current->data) == visited.end()) {
                    visited.insert(current->data);
                    q.push(current->data);
                }
                current = current->next;
            }
        }
    }
};

int main() {
    Graph graph;
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
        graph.addEdge(u, v);
    }

    string startNode;
    cout << "Enter the starting landmark for DFS and BFS: ";
    cin >> startNode;

    cout << "DFS Traversal: ";
    unordered_set<string> visited;
    graph.dfs(startNode, visited);
    cout << endl;

    cout << "BFS Traversal: ";
    graph.bfs(startNode);
    cout << endl;

    return 0;
}
