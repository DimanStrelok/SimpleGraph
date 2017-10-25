#pragma once

#include <iostream>
#include <unordered_set>

#include "Node.h"

class Graph {
    std::unordered_set<Node> nodes;
public:
    Graph() = default;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    friend std::istream& operator>>(std::istream& is, Graph& graph);

    void addNode(const Node::NodeName& name);

    Node findNode(const Node::NodeName& name) const;

    void addEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight);

    size_t countNodes() const;

    std::unordered_set<Node> getNodes() const;
};