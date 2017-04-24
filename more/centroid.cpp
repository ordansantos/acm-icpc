#include <bits/stdc++.h>

using namespace std;

void dfs1(int v, int parent, int &far, vector <int> *tree, int &maxx, int d = 0){
    if (d > maxx)
        maxx = d, far = v;
    for (int u: tree[v])
        if (u != parent)
            dfs1(u, v, far, tree, maxx, d + 1);
}

void dfs2(int v, int parent, int t, vector<int> &path, pair<int, int> &ret, vector <int> *tree){
    path.push_back(v);
    if (v == t) ret.first = path[path.size()/2], ret.second = path[(path.size()-1)/2];
    for (int u: tree[v])
        if (u != parent)
            dfs2(u, v, t, path, ret, tree);
    path.pop_back();
}

// [1..n]
pair <int, int> get_centroids(vector <int> *tree, int n){
    int farA, farB, maxx = -1;
    dfs1(1, 1, farA, tree, maxx);     // Check initial vertex
    maxx = -1;
    dfs1(farA, farA, farB, tree, maxx);
    vector <int> path;
    path.reserve(n * 2);
    pair <int, int> ret;
    dfs2(farA, farA, farB, path, ret, tree);
    return ret;
}



