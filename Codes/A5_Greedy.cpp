// Assignment 5: Greedy Algorithms
// I: Selection Sort | II: Kruskal's MST | III: Prim's MST
// No global variables | STL friendly | Parameter passing style
#include<iostream>
#include<vector>
using namespace std;

// =============================================
// I. SELECTION SORT
// =============================================
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < n; j++)
            if(arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

// =============================================
// II. KRUSKAL'S MST
// =============================================
struct Edge {
    int u, v, w;
};

int findParent(int x, vector<int>& parent) {
    if(parent[x] != x) parent[x] = findParent(parent[x], parent);
    return parent[x];
}

void kruskal() {
    int V, E;
    cout << "Enter vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge (u v weight):\n";
    for(int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    // Sort edges by weight
    for(int i = 0; i < E - 1; i++)
        for(int j = 0; j < E - i - 1; j++)
            if(edges[j].w > edges[j+1].w)
                swap(edges[j], edges[j+1]);

    vector<int> parent(V);
    for(int i = 0; i < V; i++) parent[i] = i;

    cout << "\nKruskal's MST Edges:\n";
    int total = 0, edgeCount = 0;
    for(int i = 0; i < E && edgeCount < V - 1; i++) {
        int u = findParent(edges[i].u, parent);
        int v = findParent(edges[i].v, parent);
        if(u != v) {
            cout << edges[i].u << " - " << edges[i].v << " : " << edges[i].w << "\n";
            total += edges[i].w;
            parent[u] = v;
            edgeCount++;
        }
    }
    cout << "Total MST Cost: " << total << "\n";
}

// =============================================
// III. PRIM'S MST
// =============================================
void prims() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter adjacency matrix:\n";
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            cin >> graph[i][j];

    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    key[0] = 0;

    cout << "\nPrim's MST Edges:\n";
    int total = 0;
    for(int count = 0; count < V; count++) {
        // Find min key vertex not in MST
        int u = -1;
        for(int i = 0; i < V; i++)
            if(!inMST[i] && (u == -1 || key[i] < key[u])) u = i;

        inMST[u] = true;
        if(parent[u] != -1) {
            cout << parent[u] << " - " << u << " : " << key[u] << "\n";
            total += key[u];
        }

        // Update key values for adjacent vertices
        for(int v = 0; v < V; v++) {
            if(!inMST[v] && graph[u][v] != 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    cout << "Total MST Cost: " << total << "\n";
}

// =============================================
// MAIN MENU
// =============================================
int main() {
    int choice;
    cout << "===== Greedy Algorithms =====\n";
    cout << "1. Selection Sort\n";
    cout << "2. Kruskal's MST\n";
    cout << "3. Prim's MST\n";
    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1) {
        int n;
        cout << "Enter number of elements: ";
        cin >> n;
        vector<int> arr(n);
        cout << "Enter elements: ";
        for(int i = 0; i < n; i++) cin >> arr[i];
        selectionSort(arr);
        cout << "Sorted: ";
        for(int x : arr) cout << x << " ";
        cout << "\n";
    }
    else if(choice == 2) kruskal();
    else if(choice == 3) prims();

    return 0;
}

/*
Prim's sample (4 vertices):
Matrix:
0 10 6 5
10 0 0 15
6 0 0 4
5 15 4 0
Output: 0-3:5, 3-2:4, 0-1:10 = Total 19

Kruskal sample (4 vertices, 5 edges):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
MST: 2-3:4, 0-3:5, 0-1:10 = Total 19
*/
