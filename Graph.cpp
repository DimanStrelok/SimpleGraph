#include "Graph.h"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    os << "Graph " << graph.nodes.size() << std::endl;
    size_t i = 0;
    size_t max = graph.nodes.size() - 1;
    for (auto&& node : graph.nodes) {
        if (i < max) {
            os << node << std::endl;
        } else {
            os << node;
        }
        i++;
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

Node Graph::findNode(const Node::NodeName& name) const {
    auto it = nodes.find(Node(name));
    return *it;
}

void Graph::addNode(const Node::NodeName& name) {
    nodes.emplace(name);
}

void Graph::renameNode(const Node::NodeName& oldName, const Node::NodeName& newName) {
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

void Graph::removeNode(const Node::NodeName& name) {
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

void Graph::addEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight) {
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

void Graph::updateEdge(const Node::NodeName& from, const Node::NodeName& to, Node::EdgeWeight weight) {
    auto it_from = nodes.find(from);
    auto it_to = nodes.find(to);
    Node n_from = *it_from;
    Node n_to = *it_to;
    nodes.erase(it_from);
    nodes.erase(it_to);
    n_from.updateEdge(to, weight);
    n_to.updateEdge(to, weight);
    nodes.insert(n_from);
    nodes.insert(n_to);
}

void Graph::removeEdge(const Node::NodeName& from, const Node::NodeName& to) {
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

std::unordered_set<Node> Graph::getNodes() const {
    return nodes;
}