#include "queries.h"
#include "bfs.h"
#include "util.h"

#include <iostream>
#include <limits>

using std::cout;
using std::cerr;
using std::endl;

static const int INF_INT = std::numeric_limits<int>::max();

// ---------- Question 1: A -> B with max connections ----------
void handleQuestion1(const Graph &g,
                     const std::string &cityA,
                     const std::string &cityB,
                     int maxConn) {
    int s = g.getId(cityA);
    int t = g.getId(cityB);

    if (s == -1) {
        cout << "Unknown city: " << cityA << "\n";
        return;
    }
    if (t == -1) {
        cout << "Unknown city: " << cityB << "\n";
        return;
    }

    BFSResult res = bfs(g, s);

    if (res.dist[t] == INF_INT) {
        cout << "No such route.\n";
        return;
    }

    int connections = res.dist[t];

    if (connections > maxConn) {
        cout << "No route with less than " << maxConn << " connections.\n";
        return;
    }

    std::vector<int> path = reconstructPath(s, t, res.parent);
    printPath(g, path, cout);
    cout << "\n";
    cout << "total connection: " << connections << "\n";
}

// ---------- Question 2: A -> D via B and C in any order ----------
void handleQuestion2(const Graph &g,
                     const std::string &A,
                     const std::string &B,
                     const std::string &C,
                     const std::string &D) {
    int a = g.getId(A);
    int b = g.getId(B);
    int c = g.getId(C);
    int d = g.getId(D);

    if (a == -1 || b == -1 || c == -1 || d == -1) {
        if (a == -1) cout << "Unknown city: " << A << "\n";
        if (b == -1) cout << "Unknown city: " << B << "\n";
        if (c == -1) cout << "Unknown city: " << C << "\n";
        if (d == -1) cout << "Unknown city: " << D << "\n";
        return;
    }

    BFSResult bfsA = bfs(g, a);
    BFSResult bfsB = bfs(g, b);
    BFSResult bfsC = bfs(g, c);

    // Order 1: A -> B -> C -> D
    bool valid1 = (bfsA.dist[b] < INF_INT &&
                   bfsB.dist[c] < INF_INT &&
                   bfsC.dist[d] < INF_INT);

    long long len1 = valid1
        ? (long long)bfsA.dist[b] + bfsB.dist[c] + bfsC.dist[d]
        : (long long)4 * INF_INT;

    // Order 2: A -> C -> B -> D
    bool valid2 = (bfsA.dist[c] < INF_INT &&
                   bfsC.dist[b] < INF_INT &&
                   bfsB.dist[d] < INF_INT);

    long long len2 = valid2
        ? (long long)bfsA.dist[c] + bfsC.dist[b] + bfsB.dist[d]
        : (long long)4 * INF_INT;

    if (!valid1 && !valid2) {
        cout << "No such route.\n";
        return;
    }

    std::vector<int> finalPath;
    long long bestLen;

    if (valid1 && (!valid2 || len1 <= len2)) {
        // Use A -> B -> C -> D
        auto pAB = reconstructPath(a, b, bfsA.parent);
        auto pBC = reconstructPath(b, c, bfsB.parent);
        auto pCD = reconstructPath(c, d, bfsC.parent);
        if (pAB.empty() || pBC.empty() || pCD.empty()) {
            cout << "No such route.\n";
            return;
        }
        auto tmp = concatPaths(pAB, pBC);
        finalPath = concatPaths(tmp, pCD);
        bestLen = len1;
    } else {
        // Use A -> C -> B -> D
        auto pAC = reconstructPath(a, c, bfsA.parent);
        auto pCB = reconstructPath(c, b, bfsC.parent);
        auto pBD = reconstructPath(b, d, bfsB.parent);
        if (pAC.empty() || pCB.empty() || pBD.empty()) {
            cout << "No such route.\n";
            return;
        }
        auto tmp = concatPaths(pAC, pCB);
        finalPath = concatPaths(tmp, pBD);
        bestLen = len2;
    }

    printPath(g, finalPath, cout);
    cout << "\n";
    cout << "smallest number of connection: " << bestLen << "\n";
}

// ---------- Question 3: Best meeting city for A, B, C ----------
void handleQuestion3(const Graph &g,
                     const std::string &A,
                     const std::string &B,
                     const std::string &C) {
    int a = g.getId(A);
    int b = g.getId(B);
    int c = g.getId(C);

    if (a == -1 || b == -1 || c == -1) {
        if (a == -1) cout << "Unknown city: " << A << "\n";
        if (b == -1) cout << "Unknown city: " << B << "\n";
        if (c == -1) cout << "Unknown city: " << C << "\n";
        return;
    }

    BFSResult bfsA = bfs(g, a);
    BFSResult bfsB = bfs(g, b);
    BFSResult bfsC = bfs(g, c);

    int n = g.numCities();
    long long bestSum = (long long)4 * INF_INT;
    int bestCity = -1;

    for (int v = 0; v < n; ++v) {
        if (v == a || v == b || v == c) continue;
        if (bfsA.dist[v] == INF_INT ||
            bfsB.dist[v] == INF_INT ||
            bfsC.dist[v] == INF_INT) {
            continue;
        }
        long long total = (long long)bfsA.dist[v] +
                          bfsB.dist[v] +
                          bfsC.dist[v];
        if (total < bestSum) {
            bestSum = total;
            bestCity = v;
        }
    }

    if (bestCity == -1) {
        cout << "There is no such meeting city.\n";
        return;
    }

    cout << "You three should meet at " << g.getName(bestCity) << "\n";

    auto pathA = reconstructPath(a, bestCity, bfsA.parent);
    auto pathB = reconstructPath(b, bestCity, bfsB.parent);
    auto pathC = reconstructPath(c, bestCity, bfsC.parent);

    cout << "Route for first person: ";
    printPath(g, pathA, cout);
    cout << " (" << bfsA.dist[bestCity] << " connections)\n";

    cout << "Route for second person: ";
    printPath(g, pathB, cout);
    cout << " (" << bfsB.dist[bestCity] << " connections)\n";

    cout << "Route for third person: ";
    printPath(g, pathC, cout);
    cout << " (" << bfsC.dist[bestCity] << " connections)\n";

    cout << "Total number of connection: " << bestSum << "\n";
}