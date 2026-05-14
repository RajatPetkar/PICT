#include <bits/stdc++.h>
using namespace std;

#define MAX 100

// ================= PRIMS =================

void prims()
{
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<pair<int,int>> adj[MAX];

    cout << "Enter u v w:\n";

    for(int i=0;i<e;i++)
    {
        int u,v,w;
        cin >> u >> v >> w;

        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
    }

    vector<int> key(n,INT_MAX);
    vector<bool> mst(n,false);

    priority_queue<pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>> pq;

    key[0]=0;
    pq.push({0,0});

    int total=0;

    while(!pq.empty())
    {
        int u=pq.top().second;
        int w=pq.top().first;
        pq.pop();

        if(mst[u]) continue;

        mst[u]=true;
        total += w;

        for(auto x:adj[u])
        {
            int weight=x.first;
            int v=x.second;

            if(!mst[v] && weight<key[v])
            {
                key[v]=weight;
                pq.push({weight,v});
            }
        }
    }

    cout << "Minimum Cost = " << total << endl;
}

// ================= KRUSKAL =================

struct Edge
{
    int u,v,w;
};

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

int parent[100];

int findSet(int x)
{
    if(parent[x]==x)
        return x;

    return parent[x]=findSet(parent[x]);
}

void unite(int a,int b)
{
    parent[findSet(a)] = findSet(b);
}

void kruskal()
{
    int v,e;

    cout << "Enter number of vertices: ";
    cin >> v;

    cout << "Enter number of edges: ";
    cin >> e;

    Edge arr[e];

    cout << "Enter u v w:\n";

    for(int i=0;i<e;i++)
    {
        cin >> arr[i].u
            >> arr[i].v
            >> arr[i].w;
    }

    for(int i=0;i<100;i++)
        parent[i]=i;

    sort(arr,arr+e,cmp);

    int total=0;

    cout << "MST:\n";

    for(int i=0;i<e;i++)
    {
        if(findSet(arr[i].u)!=findSet(arr[i].v))
        {
            cout << arr[i].u
                 << " - "
                 << arr[i].v
                 << " = "
                 << arr[i].w
                 << endl;

            total += arr[i].w;

            unite(arr[i].u,arr[i].v);
        }
    }

    cout << "Total Cost = " << total << endl;
}

// ================= JOB SCHEDULING =================

struct Job
{
    char id;
    int deadline;
    int profit;
};

bool cmpJob(Job a, Job b)
{
    return a.profit > b.profit;
}

void jobScheduling()
{
    int n;

    cout << "Enter number of jobs: ";
    cin >> n;

    Job arr[n];

    cout << "Enter id deadline profit:\n";

    for(int i=0;i<n;i++)
    {
        cin >> arr[i].id
            >> arr[i].deadline
            >> arr[i].profit;
    }

    sort(arr,arr+n,cmpJob);

    int maxDeadline=0;

    for(int i=0;i<n;i++)
    {
        maxDeadline=max(maxDeadline,arr[i].deadline);
    }

    vector<char> slot(maxDeadline,0);

    int total=0;

    for(int i=0;i<n;i++)
    {
        for(int j=arr[i].deadline-1;j>=0;j--)
        {
            if(slot[j]==0)
            {
                slot[j]=arr[i].id;
                total += arr[i].profit;
                break;
            }
        }
    }

    cout << "Scheduled Jobs:\n";

    for(int i=0;i<maxDeadline;i++)
    {
        if(slot[i]!=0)
            cout << slot[i] << " ";
    }

    cout << "\nTotal Profit = " << total << endl;
}

// ================= DIJKSTRA =================

void dijkstra()
{
    int n,e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<pair<int,int>> adj[n];

    cout << "Enter u v w:\n";

    for(int i=0;i<e;i++)
    {
        int u,v,w;

        cin >> u >> v >> w;

        adj[u].push_back({v,w});
    }

    int source;

    cout << "Enter source: ";
    cin >> source;

    vector<int> dist(n,INT_MAX);

    dist[source]=0;

    priority_queue<pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>> pq;

    pq.push({0,source});

    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();

        for(auto x:adj[u])
        {
            int v=x.first;
            int w=x.second;

            if(dist[v] > dist[u]+w)
            {
                dist[v]=dist[u]+w;

                pq.push({dist[v],v});
            }
        }
    }

    cout << "Shortest Distances:\n";

    for(int i=0;i<n;i++)
    {
        cout << source
             << " -> "
             << i
             << " = ";

        if(dist[i]==INT_MAX)
            cout << "INF";
        else
            cout << dist[i];

        cout << endl;
    }
}

// ================= SELECTION SORT =================

void selectionSort()
{
    int n;

    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements:\n";

    for(int i=0;i<n;i++)
        cin >> arr[i];

    for(int i=0;i<n-1;i++)
    {
        int minIndex=i;

        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[minIndex])
            {
                minIndex=j;
            }
        }

        swap(arr[i],arr[minIndex]);
    }

    cout << "Sorted Array:\n";

    for(int i=0;i<n;i++)
        cout << arr[i] << " ";
}

// ================= MAIN =================

int main()
{
    int choice;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Prims Algorithm\n";
        cout << "2. Kruskal Algorithm\n";
        cout << "3. Job Scheduling\n";
        cout << "4. Dijkstra Algorithm\n";
        cout << "5. Selection Sort\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                prims();
                break;

            case 2:
                kruskal();
                break;

            case 3:
                jobScheduling();
                break;

            case 4:
                dijkstra();
                break;

            case 5:
                selectionSort();
                break;

            case 6:
                cout << "Program Ended";
                break;

            default:
                cout << "Invalid Choice";
        }

    } while(choice != 6);

    return 0;
}
