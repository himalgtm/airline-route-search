#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

class Graph {
public:
    // Add (or get existing) city ID
    int addCity(const std::string &name);

    // Get city ID, or -1 if not found
    int getId(const std::string &name) const;

    // Get city name by ID
    const std::string &getName(int id) const;

    // Add directed edge from -> to
    void addEdge(const std::string &from, const std::string &to);

    // Adjacency list access
    const std::vector<std::vector<int>> &getAdj() const { return adj; }

    // Number of cities
    int numCities() const { return (int)id_to_name.size(); }

    // Load flight data from file (see graph.cpp)
    void loadFromFile(const std::string &filename);

private:
    std::unordered_map<std::string,int> name_to_id;
    std::vector<std::string> id_to_name;
    std::vector<std::vector<int>> adj;
};

#endif // GRAPH_H