#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

int parent[100];

int find(int x) {
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int a, int b) {
    parent[find(a)] = find(b);
}

int main() {
    Edge e[] = {{0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}};
    int n = 6;

    for(int i = 0; i < 100; i++) parent[i] = i;

    sort(e, e+n, cmp);

    for(int i = 0; i < n; i++) {
        if(find(e[i].u) != find(e[i].v)) {
            cout << e[i].u << "-" << e[i].v << " ";
            unite(e[i].u, e[i].v);
        }
    }
}