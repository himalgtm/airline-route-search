#ifndef BFS_H
#define BFS_H

#include <vector>
#include "graph.h"

struct BFSResult {
    std::vector<int> dist;
    std::vector<int> parent;
};

BFSResult bfs(const Graph &g, int src);

#endif // BFS_H
