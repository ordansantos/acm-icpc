const int N = 100005; // number of Nodes [1..n]
struct APB {
    bool isArticulation[N];
    vector <int> *graph;
    int num[N], low[N], rootChildren, cnt, n;
    // 1..N
    APB(int n, vector<int> *graph){
        this->graph = graph;
        this->n = n;
        memset(isArticulation, false, sizeof isArticulation);
        memset(num, 0, sizeof num);
    }

    void solve (){
        cnt = 1;
        for (int i = 1; i <= n; i++){
            if (!num[i]){
                rootChildren = 0;
                dfs(i, i);
                isArticulation[i] = rootChildren > 1;
            }
        }
    }

    void dfs (int v, int pai){
        num[v] = low[v] = cnt++;
        for (int i = 0; i < graph[v].size(); i++){
            int u = graph[v][i];
            if (!num[u]){
                if (v == 1) rootChildren++;
                dfs (u, v);
                if (num[v] <= low[u])
                    isArticulation[v] = true;
                /*
                if (numv[v] < low[u])
                    ponte!
                */
                low[v] = min (low[v], low[u]);
            } else
                if (u != pai)
                    low[v] = min (low[v], num[u]);
        }
    }

};
