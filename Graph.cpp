#include "Graph.h"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    os << "Graph " << graph.nodes.size() << std::endl;
    bool first = true;
    for (auto&& node : graph.nodes) {
        if (!first) {
            os << std::endl;
        }
        first = false;
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

Node Graph::findNode(const std::string& name) const {
    auto it = nodes.find(name);
    return *it;
}

void Graph::addNode(const std::string& name) {
    nodes.emplace(name);
}

void Graph::renameNode(const std::string& oldName, const std::string& newName) {
    auto it = nodes.find(oldName);
    Node n = *it;
    nodes.erase(it);
    for (auto&& e : n.edges) {
        auto itt = nodes.find(e.first);
        Node t = *itt;
        nodes.erase(itt);
        auto itn = t.edges.find(n.name);
        auto en = *itn;
        t.edges.erase(itn);
        t.edges.emplace(newName, en.second);
        nodes.insert(t);
    }
    n.name = newName;
    nodes.insert(n);
}

void Graph::removeNode(const std::string& name) {
    auto it = nodes.find(name);
    Node n = *it;
    nodes.erase(it);
    for (auto&& e : n.edges) {
        auto itt = nodes.find(e.first);
        Node t = *itt;
        nodes.erase(itt);
        t.edges.erase(n.name);
        nodes.insert(t);
    }
}

void Graph::addEdge(const std::string& from, const std::string& to, double weight) {
    auto it_from = nodes.find(from);
    auto it_to = nodes.find(to);
    Node n_from = *it_from;
    Node n_to = *it_to;
    nodes.erase(it_from);
    nodes.erase(it_to);
    n_from.addEdge(to, weight);
    n_to.addEdge(from, weight);
    nodes.insert(n_from);
    nodes.insert(n_to);
}

void Graph::updateEdge(const std::string& from, const std::string& to, double weight) {
    auto it_from = nodes.find(from);
    auto it_to = nodes.find(to);
    Node n_from = *it_from;
    Node n_to = *it_to;
    nodes.erase(it_from);
    nodes.erase(it_to);
    n_from.updateEdge(to, weight);
    n_to.updateEdge(from, weight);
    nodes.insert(n_from);
    nodes.insert(n_to);
}

void Graph::removeEdge(const std::string& from, const std::string& to) {
    auto it_from = nodes.find(from);
    auto it_to = nodes.find(to);
    Node n_from = *it_from;
    Node n_to = *it_to;
    nodes.erase(it_from);
    nodes.erase(it_to);
    n_from.removeEdge(to);
    n_to.removeEdge(from);
    nodes.insert(n_from);
    nodes.insert(n_to);
}

size_t Graph::countNodes() const {
    return nodes.size();
}

std::set<Node> Graph::getNodes() const {
    return nodes;
}