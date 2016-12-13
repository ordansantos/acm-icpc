
// It also solves with negative edges and MCBM in a viable time
struct SSP {
    int n, source, sink;
    vector<vector<int> > adj;
    struct edge {
        int u, flow, cap, cost, origcost;
    };
    vector<edge> edges;
    SSP(int n, int source, int sink) : n(n), source(source), sink(sink), adj(n){}
    int add_edge(int a, int b, int cap, int cost){
        int result = edges.size();
        adj[a].push_back(edges.size());
        edges.push_back({ b, 0, cap, cost, cost });
        adj[b].push_back(edges.size());
        edges.push_back({ a, 0, 0, -cost, -cost });
        return result;
    }
    pair<int, int> iterate(){
        struct state_t {
            int dist, prev, maxf;
        };
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        vector<state_t> states(n, { INT_MAX / 2, -1, 0 });
        states[source] = { 0, -2, INT_MAX };
        pq.push(make_pair(states[source].dist, source));
        while (!pq.empty()) {
            int d, v;
            tie(d, v) = pq.top();
            pq.pop();
            if (d != states[v].dist)
                continue;
            for (int edid : adj[v]) {
                edge& ed = edges[edid];
                if (ed.flow < ed.cap && states[ed.u].dist > states[v].dist + ed.cost) {
                    states[ed.u].dist = states[v].dist + ed.cost;
                    states[ed.u].prev = edid;
                    states[ed.u].maxf = min(states[v].maxf, ed.cap - ed.flow);

                    pq.push(make_pair(states[ed.u].dist, ed.u));
                }
            }
        }
        int lastid = states[sink].prev, extraflow = states[sink].maxf, atcost = 0;
        if (lastid == -1)
            return { 0, 0 };
        for (int id = lastid; id != -2; id = states[edges[id ^ 1].u].prev) {
            edges[id].flow += extraflow;
            edges[id ^ 1].flow -= extraflow;
            atcost += edges[id].origcost;
        }
        for (int id = 0; id < (int)edges.size(); ++id) {
            int v = edges[id ^ 1].u, u = edges[id].u;
            if (states[v].prev != -1 && states[u].prev != -1)
                edges[id].cost += states[v].dist - states[u].dist;
        }
        return { extraflow, atcost };
    }
    pair<int, int> mfmc()
    {
        int flow = 0, cost = 0;
        if (any_of(edges.begin(), edges.end(),
                [](const edge& ed) { return ed.flow > 0 && ed.cost < 0; }))
            bellmanford();
        int extraflow, atcost;
        while (tie(extraflow, atcost) = iterate(), extraflow > 0)
            flow += extraflow, cost += extraflow * atcost;
        return { flow, cost };
    }
    void bellmanford()
    {
        vector<int> dist(n, INT_MAX / 2);
        dist[source] = 0;
        for (int rep = 0; rep < n; ++rep) {
            bool changed = false;
            for (int id = 0; id < (int)edges.size(); ++id) {
                int v = edges[id ^ 1].u, u = edges[id].u;
                if (edges[id].flow < edges[id].cap && dist[v] != INT_MAX / 2 && dist[u] > dist[v] + edges[id].cost) {
                    dist[u] = dist[v] + edges[id].cost;
                    changed = true;
                    assert(rep < n - 1); // Negative cycle found .
                }
            }
            if (!changed)
                break;
        }
        for (int id = 0; id < (int)edges.size(); ++id) {
            int v = edges[id ^ 1].u, u = edges[id].u;
            if (dist[v] < INT_MAX / 2 && dist[u] < INT_MAX / 2)
                edges[id].cost += dist[v] - dist[u];
        }
    }
};

