#include "util.h"
#include <algorithm>

std::vector<int> reconstructPath(int src, int dst, const std::vector<int> &parent) {
    std::vector<int> path;
    int cur = dst;

    while (cur != -1) {
        path.push_back(cur);
        if (cur == src) break;
        cur = parent[cur];
    }

    if (path.empty() || path.back() != src) {
        // unreachable
        return {};
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> concatPaths(const std::vector<int> &p1, const std::vector<int> &p2) {
    if (p1.empty() || p2.empty()) return {};
    std::vector<int> res = p1;
    int startIdx = 0;
    if (!res.empty() && !p2.empty() && res.back() == p2.front()) {
        startIdx = 1;
    }
    for (int i = startIdx; i < (int)p2.size(); ++i) {
        res.push_back(p2[i]);
    }
    return res;
}

void printPath(const Graph &g, const std::vector<int> &path, std::ostream &out) {
    for (size_t i = 0; i < path.size(); ++i) {
        out << g.getName(path[i]);
        if (i + 1 < path.size()) out << " to ";
    }
}