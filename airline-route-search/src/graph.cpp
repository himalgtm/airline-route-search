#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// simple trim helper
static std::string trim(const std::string &s) {
    std::string res = s;
    // left trim
    res.erase(res.begin(),
              std::find_if(res.begin(), res.end(),
                           [](unsigned char ch){ return !std::isspace(ch); }));
    // right trim
    res.erase(std::find_if(res.rbegin(), res.rend(),
                           [](unsigned char ch){ return !std::isspace(ch); }).base(),
              res.end());
    return res;
}

int Graph::addCity(const std::string &name) {
    auto it = name_to_id.find(name);
    if (it != name_to_id.end()) return it->second;
    int id = (int)id_to_name.size();
    name_to_id[name] = id;
    id_to_name.push_back(name);
    adj.emplace_back();
    return id;
}

int Graph::getId(const std::string &name) const {
    auto it = name_to_id.find(name);
    if (it == name_to_id.end()) return -1;
    return it->second;
}

const std::string &Graph::getName(int id) const {
    return id_to_name[id];
}

void Graph::addEdge(const std::string &from, const std::string &to) {
    int u = addCity(from);
    int v = addCity(to);
    adj[u].push_back(v);
}

void Graph::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "ERROR: Cannot open flight data file: " << filename << "\n";
        std::exit(1);
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line)) {
        ++lineNum;
        if (line.empty()) continue;

        // Expected format per line (CSV):
        // New York, Chicago, 790
        std::stringstream ss(line);
        std::string fromRaw, toRaw, distRaw;

        if (!std::getline(ss, fromRaw, ',')) continue;
        if (!std::getline(ss, toRaw, ',')) continue;
        if (!std::getline(ss, distRaw)) continue;  // everything after 2nd comma

        std::string from = trim(fromRaw);
        std::string to   = trim(toRaw);
        std::string distStr = trim(distRaw);

        if (from.empty() || to.empty()) {
            std::cerr << "WARNING: Skipping malformed line " << lineNum
                      << ": " << line << "\n";
            continue;
        }

        // distance is not used for the algorithms, but can sanity-check it
        try {
            (void)std::stod(distStr); // just to validate; value ignored
        } catch (...) {
            // not a issue if it's not a valid number, still add the edge.
        }

        addEdge(from, to);
    }
}