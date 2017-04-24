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
    dfs1(1, 1, farA, tree, maxx);       		// check initial vertex********
    maxx = -1;
    dfs1(farA, farA, farB, tree, maxx);
    vector <int> path;
    path.reserve(n * 2);
    pair <int, int> ret;
    dfs2(farA, farA, farB, path, ret, tree);
    return ret;
}


////////////////////////////////////////////////////////
//http://wwwmayr.in.tum.de/konferenzen/Jass08/courses/1/smal/Smal_Paper.pdf

const int N = 100000; 							// check NUMBER OF NODES*********
typedef unsigned long long ULL;
ULL rh[N + 1], magic = 191;

// Get the hash of the tree
ULL dfs_hash (int v, int parent, vector<int> *tree){
    ULL ret = magic; // better than 1 :P
    vector <ULL> children;
    for (int u: tree[v])
        if (u != parent)
            children.push_back(dfs_hash(u, v, tree));
    sort (children.begin(), children.end());
    for (int i = 0; i < children.size(); i++)
        ret += children[i] * rh[i];
    return ret;
}

// This function does everything!
// Get the two possibles hashs, depends on the center
// Bidirected tree
pair<ULL, ULL> hash_tree(vector <int> *tree, int n){
    if (rh[0] == 0) for (int i = 0; i <= N; i++) while (!(rh[i] = rand()));
    pair <int, int> centroid = get_centroids(tree, n);
    ULL h1 = dfs_hash(centroid.first, centroid.first, tree);
    ULL h2 = dfs_hash(centroid.second, centroid.second, tree);
    if (h1 > h2) swap (h1, h2);
    return {h1, h2};
}

