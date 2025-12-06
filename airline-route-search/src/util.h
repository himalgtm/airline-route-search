#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>

#include "graph.h"

// Reconstruct path from src to dst using parent array; returns empty vector if unreachable
std::vector<int> reconstructPath(int src, int dst, const std::vector<int> &parent);

// Concatenate two paths, avoiding duplicate joint city
std::vector<int> concatPaths(const std::vector<int> &p1, const std::vector<int> &p2);

// Pretty print a path as "CityA to CityB to CityC..."
void printPath(const Graph &g, const std::vector<int> &path, std::ostream &out = std::cout);

#endif // UTIL_H