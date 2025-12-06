#ifndef QUERIES_H
#define QUERIES_H

#include <string>
#include "graph.h"

// Q1: Shortest path A -> B with constraint on max connections
void handleQuestion1(const Graph &g,
                     const std::string &cityA,
                     const std::string &cityB,
                     int maxConn);

// Q2: Shortest A -> D path through B and C (order free)
void handleQuestion2(const Graph &g,
                     const std::string &A,
                     const std::string &B,
                     const std::string &C,
                     const std::string &D);

// Q3: Best meeting city for A, B, C
void handleQuestion3(const Graph &g,
                     const std::string &A,
                     const std::string &B,
                     const std::string &C);

#endif // QUERIES_H