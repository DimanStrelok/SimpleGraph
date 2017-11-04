#include "Node.h"

Node::Node(const NodeName& name_) : name(name_) {}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Name node: " << node.name << std::endl;
    os << "Edges " << node.edges.size() << std::endl;
    size_t i = 0;
    size_t max = node.edges.size() - 1;
    for (auto&& edge : node.edges) {
        if (i < max) {
            os << edge.first << ' ' << edge.second << std::endl;
        } else {
            os << edge.first << ' ' << edge.second;
        }
        i++;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Node& node) {
    std::string temp;
    is >> temp >> temp >> node.name;
    size_t n;
    is >> temp >> n;
    for (size_t i = 0; i < n; i++) {
        Node::NodeName t1;
        Node::EdgeWeight t2;
        is >> t1 >> t2;
        node.edges.emplace(t1, t2);
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

void Node::addEdge(const NodeName& to, EdgeWeight weight) {
    edges.emplace(to, weight);
}

void Node::updateEdge(const NodeName& to, EdgeWeight weight) {
    edges.erase(to);
    edges.emplace(to, weight);
}

void Node::removeEdge(const Node::NodeName& to) {
    edges.erase(to);
}