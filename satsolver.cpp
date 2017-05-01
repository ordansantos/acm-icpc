
struct satSolver {
    // SZ must be 2 times number of variables
    vector <int> graph[SZ], rgraph[SZ];
    int n, visited[SZ], component[SZ];

    satSolver (int n) : n(n) {}

    // [1..n], use -a for not a
    void add_formula (int a, int b){
        a = get_value(a);
        b = get_value(b);
        graph[a^1].push_back (b);
        graph[b^1].push_back (a);
    }

    int get_value(int v){
        return 2 * (abs (v) - 1) ^ (v < 0);
    }

    void solve (){
        for (int v = 0; v < 2 * n; v++)
            for (int u: graph[v])
                rgraph[u].push_back (v);
        stack <int> s;
        memset(visited, false, sizeof visited);
        for (int i = 0; i < 2 * n; i++) dfs1(i, s);
        memset(visited, false, sizeof visited);

        int c = 0;
        while (!s.empty()){
            int v = s.top();
            s.pop();
            dfs2 (v, c++);
        }
    }

    void dfs1 (int v, stack <int> &s){
        if (visited[v]) return;
        visited[v] = true;
        for (int u: graph[v])
            dfs1(u, s);
        s.push(v);
    }

    void dfs2 (int v, int c){
        if (visited[v]) return;
        visited[v] = true;
        component[v] = c;
        for (int u: rgraph[v]) dfs2 (u, c);
    }

    bool is_possible (){
        for (int i = 1; i <= n; i++)
            if (component[get_value(i)] == component[get_value(-i)]) return false;
        return true;
    }

    bool trueorfalse (int i){
        if (component[get_value(-i)] < component[get_value(i)]) return true;
        return false;
    }

};
// a == b: (a || !b) && (!a || b)
// a != b: (a || b) && (!a || !b)
