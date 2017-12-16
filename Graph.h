#pragma once

#include <iostream>
#include <set>

#include "Node.h"

class Graph {
    std::set<Node> nodes;
public:
    Graph() = default;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    friend std::istream& operator>>(std::istream& is, Graph& graph);

    Node findNode(const std::string& name) const;

    void addNode(const std::string& name);

    void renameNode(const std::string& oldName, const std::string& newName);

    void removeNode(const std::string& name);

    void addEdge(const std::string& from, const std::string& to, double weight);

    void updateEdge(const std::string& from, const std::string& to, double weight);

    void removeEdge(const std::string& from, const std::string& to);

    size_t countNodes() const;

    std::set<Node> getNodes() const;
};