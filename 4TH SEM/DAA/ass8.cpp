#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void optimalBST(vector<int>& keys, vector<int>& p, int n) {
    
    vector<vector<int>> e(n + 2, vector<int>(n + 1, 0)); 
    vector<vector<int>> w(n + 2, vector<int>(n + 1, 0)); 
    
 
    for (int i = 1; i <= n; ++i) {
        e[i][i] = p[i - 1]; 
        w[i][i] = p[i - 1]; 
    }
    
  
    for (int len = 2; len <= n; ++len) {  
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            w[i][j] = w[i][j - 1] + p[j - 1];  
        }
    }


    for (int len = 2; len <= n; ++len) {  
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            e[i][j] = INT_MAX;

         
            for (int r = i; r <= j; ++r) {
                int cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cout<<e[i][j]<<" ";
        }
        cout<<endl;
    }
   
    cout << "Minimum cost of the optimal binary search tree: " << e[1][n] << endl;
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<int> keys(n);  
    vector<int> p(n);    
    
    cout << "Enter the keys (in sorted order):\n";
    for (int i = 0; i < n; ++i) {
        cin >> keys[i];
    }

    cout << "Enter the probabilities for each key:\n";
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    optimalBST(keys, p, n);

    return 0;
}
