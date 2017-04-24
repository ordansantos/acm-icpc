#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
const int LOG = 10;

vector <int> graph[N + 1];
int table[N][LOG + 1], height[N + 1];

void dfs (int v = 1, int parent = 1){
    table[v][0] = parent;
    height[v] = height[parent] + 1;
    for (int u: graph[v]) if (u != parent) dfs(u, v);
}

void build (int n){
    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i <= n; i++)
            table[i][j] = table[table[i][j-1]][j-1];
}

int lca (int a, int b){
    if (height[a] > height[b]) swap (a, b);
    for (int i = LOG; i >= 0; i--)
        if (height[b] - (1<<i) >= height[a])
            b = table[b][i];
    if (a == b) return a;
    for (int i = LOG; i >= 0; i--)
        if (table[a][i] != table[b][i])
            a = table[a][i], b = table[b][i];
    return table[a][0];
}
