struct edge{
    int to, rev, cap, flow;
};

struct Dinic{

    static const int MAX_NODES = 5001, MAX_FLOW = 1 << 30;

    vector <edge> graph[MAX_NODES];

    int dist[MAX_NODES], ptr[MAX_NODES], s, t, n;

    void addEdge (int a, int b, int cap){
        edge e1 = {b, (int)graph[b].size(), cap, 0};
        edge e2 = {a, (int)graph[a].size(), 0, 0};
        graph[a].push_back (e1);
        graph[b].push_back (e2);
    }

    bool bfs (){
        queue <int> q;
        for (int i = 0; i < n; i++) dist[i] = -1;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()){
            int v = q.front();
            q.pop();
            for (int i = 0; i < graph[v].size(); i++){
                edge e = graph[v][i];
                if (dist[e.to] == -1 && e.flow < e.cap){
                    q.push(e.to);
                    dist[e.to] = dist[v] + 1;
                }
            }
        }
        return dist[t] != -1;
    }

    int dfs (int v, int flow){
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < graph[v].size(); ptr[v]++){
            edge &e = graph[v][ptr[v]];
            if (dist[v] + 1 != dist[e.to]) continue;
            int f = dfs (e.to, min (flow, e.cap - e.flow));
            if (f){
                e.flow += f;
                graph[e.to][e.rev].flow -= f;
                return f;
            }
        }
        return 0;
    }

    // nodes[0..qtd_nodes) !!!
    int getMaxFlow (int src, int sink, int qtd_nodes){
        s = src, t = sink, n = qtd_nodes;
        int flow = 0;
        while (bfs()){
            for (int i = 0; i < n; i++) ptr[i] = 0;
            while (int f = dfs(s, MAX_FLOW)){
                flow += f;
            }
        }
        return flow;
    }
};
