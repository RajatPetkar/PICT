#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u;
    int v;
    int w;
};
// Comparator for sorting edges
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

int parent[100];
int find(int x) {
    if(parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}
void unite(int a, int b) {
    parent[find(a)] = find(b);
}
int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;
    Edge e[edges];

    cout << "\nEnter source destination weight:\n";
    for(int i = 0; i < edges; i++) {
        cin >> e[i].u
            >> e[i].v
            >> e[i].w;
    }

    for(int i = 0; i < 100; i++) {
        parent[i] = i;
    }

    sort(e, e + edges, cmp);

    int totalCost = 0;
    cout << "\nMinimum Spanning Tree:\n";
    // Kruskal Algorithm
    for(int i = 0; i < edges; i++) {

        if(find(e[i].u) != find(e[i].v)) {

            cout << e[i].u
                 << " - "
                 << e[i].v
                 << " : "
                 << e[i].w
                 << endl;

            totalCost += e[i].w;

            unite(e[i].u, e[i].v);
        }
    }

    cout << "\nTotal Minimum Cost = "
         << totalCost;

    return 0;
}
