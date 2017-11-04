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

    Node findNode(const Node::NodeName& name) const;

    void addNode(const Node::NodeName& name);

    void renameNode(const Node::NodeName& oldName, const Node::NodeName& newName);

    void removeNode(const Node::NodeName& name);

    void addEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight);

    void updateEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight);

    void removeEdge(const Node::NodeName& from, const Node::NodeName& to);

    size_t countNodes() const;

    std::unordered_set<Node> getNodes() const;
};