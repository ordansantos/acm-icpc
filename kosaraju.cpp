struct Kosaraju {
    vector <int> *graph, *rgraph;
    int n, *component;

    // [1..n]
    Kosaraju(int n, vector<int> *graph) : n(n), graph(graph) {
        component = new int[n + 1];
        rgraph = new vector<int>[n + 1];
        for (int v = 1; v <= n; v++)
            for (auto u: graph[v])
                rgraph[u].push_back (v);
        for (int i = 1; i <= n; i++) component[i] = -1;
    }

    void solve(){
        stack <int> s;
        for (int i = 1; i <= n; i++) dfs1 (i, s);
        int componente = 1;
        while (s.size()){
            dfs2(s.top(), componente++);
            s.pop();
        }
    }

    void dfs1(int v, stack<int> &s){
        if (component[v] != -1) return;
        component[v] = 0;
        for (auto u: graph[v]) dfs1(u, s);
        s.push(v);
    }

    void dfs2(int v, int c){
        if (component[v]) return;
        component[v] = c;
        for (auto u: rgraph[v]) dfs2(u, c);
    }

};
