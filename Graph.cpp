#include "Graph.h"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    os << "Graph " << graph.nodes.size() << std::endl;
    for (auto&& node : graph.nodes) {
        os << node;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
    std::string temp;
    size_t n;
    is >> temp >> n;
    Node node;
    for (size_t i = 0; i < n; i++) {
        is >> node;
        graph.nodes.insert(std::move(node));
    }
    return is;
}

void Graph::addNode(const Node::NodeName& name) {
    nodes.emplace(name);
}

Node Graph::findNode(const Node::NodeName& name) const {
    auto it = nodes.find(Node(name));
    return *it;
}

void Graph::addEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight) {
    auto it_from = nodes.find(Node(from));
    auto it_to = nodes.find(Node(to));
    Node n_from = *it_from;
    Node n_to = *it_to;
    nodes.erase(it_from);
    nodes.erase(it_to);
    n_from.addEdge(to, weight);
    n_to.addEdge(from, weight);
    nodes.insert(n_from);
    nodes.insert(n_to);
}

size_t Graph::countNodes() const {
    return nodes.size();
}

std::unordered_set<Node> Graph::getNodes() const {
    return nodes;
}