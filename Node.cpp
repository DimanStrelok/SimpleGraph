#include "Node.h"

Node::Node(const std::string& name_) : name(name_) {}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Name node: " << node.name << std::endl;
    os << "Edges " << node.edges.size() << std::endl;
    bool first = true;
    for (auto&& edge : node.edges) {
        if (!first) {
            os << std::endl;
        }
        first = false;
        os << edge.first << ' ' << edge.second;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Node& node) {
    std::string temp;
    is >> temp >> temp >> node.name;
    size_t n;
    is >> temp >> n;
    std::string to;
    double weight;
    for (size_t i = 0; i < n; i++) {
        is >> to >> weight;
        node.edges.emplace(to, weight);
    }
    return is;
}

bool Node::operator<(const Node& rhs) const {
    return std::tie(name) < std::tie(rhs.name);
}

bool Node::operator>(const Node& rhs) const {
    return rhs < *this;
}

bool Node::operator<=(const Node& rhs) const {
    return !(*this > rhs);
}

bool Node::operator>=(const Node& rhs) const {
    return !(*this < rhs);
}

bool Node::operator==(const Node& rhs) const {
    return std::tie(name) == std::tie(rhs.name);
}

bool Node::operator!=(const Node& rhs) const {
    return !(*this == rhs);
}

void Node::addEdge(const std::string& to, double weight) {
    edges.emplace(to, weight);
}

void Node::updateEdge(const std::string& to, double weight) {
    edges.erase(to);
    edges.emplace(to, weight);
}

void Node::removeEdge(const std::string& to) {
    edges.erase(to);
}