#include "bfs.h"
#include <queue>
#include <limits>

BFSResult bfs(const Graph &g, int src) {
    const auto &adj = g.getAdj();
    int n = (int)adj.size();

    BFSResult res;
    res.dist.assign(n, std::numeric_limits<int>::max());
    res.parent.assign(n, -1);

    std::queue<int> q;
    res.dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (res.dist[v] == std::numeric_limits<int>::max()) {
                res.dist[v] = res.dist[u] + 1;
                res.parent[v] = u;
                q.push(v);
            }
        }
    }

    return res;
}