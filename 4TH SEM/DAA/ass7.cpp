#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int adjM[5][5];  
    int edges;       
    int v = 5;      
    int a, b, c;     
    vector<pair<int, pair<int, int>>> edgeList; 
public:
    
    void create_graph() {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                adjM[i][j] = 0;
            }
        }

        cout << "Enter number of edges: ";
        cin >> edges;

        cout << "Enter edges (src, dest, cost):\n";
        for (int i = 0; i < edges; i++) {
            cin >> a >> b >> c;
            adjM[a][b] = c;
            adjM[b][a] = c;
            edgeList.push_back({c, {a, b}});  
        }
    }

    
    void display_graph() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                cout << adjM[i][j] << " ";
            }
            cout << endl;
        }
    }

    int find_parent(int parent[], int i) {
        if (parent[i] == -1)
            return i;
        return find_parent(parent, parent[i]);
    }

  
    void union_sets(int parent[], int rank[], int x, int y) {
        int xroot = find_parent(parent, x);
        int yroot = find_parent(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    
    void kruskal_mst() {
        
        sort(edgeList.begin(), edgeList.end());

        int parent[v];  
        int rank[v];   

        
        for (int i = 0; i < v; i++) {
            parent[i] = -1;
            rank[i] = 0;
        }

        vector<pair<int, pair<int, int>>> mst_edges;  
        int mst_cost = 0; 
      
        for (auto& edge : edgeList) {
            int cost = edge.first;
            int src = edge.second.first;
            int dest = edge.second.second;

           
            int x = find_parent(parent, src);
            int y = find_parent(parent, dest);

       
            if (x != y) {
                mst_edges.push_back({src, {dest, cost}});
                mst_cost += cost;
                union_sets(parent, rank, x, y);
            }
        }

       
        cout << "Edges in the Minimum Spanning Tree (MST):\n";
        for (auto& edge : mst_edges) {
            cout << edge.first << " - " << edge.second.first << " (Cost: " << edge.second.second << ")\n";
        }
        cout << "Total cost of the MST: " << mst_cost << endl;
    }
};

int main() {
    Graph g;
    g.create_graph();
    g.display_graph();
    g.kruskal_mst(); 

    return 0;
}
