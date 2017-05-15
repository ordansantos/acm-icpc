#include <bits/stdc++.h>

using namespace std;

struct HopcrofKarp {

    static const int NIL = 0, INF = 1e9, N = 1001;

    vector <int> left_graph[N];
    bool visitado[N];

    int right_match[N], left_match[N], dist[N];
    int n_left;

    HopcrofKarp(int n_left) : n_left(n_left){
        for (int i = 1; i <= n_left; i++){
            left_match[i] = NIL;
        }
        memset(right_match, NIL, sizeof right_match);
    }

    void addEdge(int l, int r){
        assert (l!=NIL&&r!=NIL);
        left_graph[l].push_back(r);
    }

    bool bfs(){
        queue<int> q;
        for (int i = 1; i <= n_left; i++){
            if (left_match[i] == NIL){
                q.push(i);
                dist[i] = 0;
            } else
                dist[i] = INF;
        }
        dist[NIL] = INF;
        while (!q.empty()){
            int v = q.front();
            q.pop();
            if (dist[v] >= dist[NIL]) continue;
            for (auto u : left_graph[v]){
                if (dist[right_match[u]] > dist[v] + 1){
                    dist[right_match[u]] = dist[v] + 1;
                    q.push(right_match[u]);
                }
            }
        }

        return dist[NIL] != INF;
    }

    bool dfs (int v){

        if (v == NIL) return true;
        for (auto u : left_graph[v]){
            if (dist[right_match[u]] == dist[v] + 1){
                if (dfs(right_match[u])){
                    left_match[v] = u;
                    right_match[u] = v;
                    return true;
                }
            }
        }

        dist[v] = INF;

        return false;
    }

    int getMaxMatching (){

        int match = 0;

        while (bfs()){
            for (int i = 1; i <= n_left; i++)
                if (left_match[i] == NIL)
                    if (dfs(i))
                        match++;
        }

        return match;
    }

    void dfs_vertex_cover(int v){
        if (visitado[v]) return;
        visitado[v] = true;
        for (int i = 0; i < left_graph[v].size(); i++)
            dfs_vertex_cover(right_match[left_graph[v][i]]);
    }

    // call matching first
    pair<vector<int>, vector<int>> vertex_cover(){
        memset(visitado, false, sizeof visitado);
        vector <int> left, right;

        for (int i = 1; i <= n_left; i++)
            if (left_match[i] == NIL)
                dfs_vertex_cover(i);

        for (int i = 1; i <= n_left; i++){
            if (!visitado[i])
                left.push_back(i);
            if (visitado[right_match[left_match[i]]])
                right.push_back(left_match[i]);
        }

        return make_pair(left, right);
    }

};

int main(){
    int n, m, p;
    while (scanf ("%d %d %d", &n, &m, &p) && n && m && p){
        HopcrofKarp hk(n);
        while (p--){
            int a, b;
            scanf ("%d %d", &a, &b);
            hk.addEdge(a, b);
        }
        printf ("%d", hk.getMaxMatching());
        pair<vector <int>, vector<int>> cover = hk.vertex_cover();
        for (int i = 0; i < cover.first.size(); i++)
            printf (" r%d", cover.first[i]);
        for (int i = 0; i < cover.second.size(); i++)
            printf (" c%d", cover.second[i]);
        printf ("\n");
    }
    return 0;
}



