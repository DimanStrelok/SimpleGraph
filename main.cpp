#include <iostream>
#include <queue>
#include <unordered_map>

#include "Graph.h"

void dijkstra_search(const Graph& graph, const std::string& start, std::unordered_map<Node::NodeName, Node::NodeName>& came_from,
                     std::unordered_map<Node::NodeName, Node::EdgeWeight>& cost_so_far) {
    using Edge = std::pair<Node, Node::EdgeWeight>;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<>> frontier;
    Node s = graph.findNode(start);
    frontier.emplace(s, 0);
    came_from[start] = start;
    cost_so_far[start] = 0;
    while (!frontier.empty()) {
        auto current = frontier.top().first;
        auto dist = frontier.top().second;
        frontier.pop();
        if (dist > cost_so_far.at(current.name)) {
            continue;
        }
        for (auto&& next : current.edges) {
            Node::EdgeWeight new_cost = cost_so_far[current.name] + next.second;
            if (cost_so_far.count(next.first) == 0 || new_cost < cost_so_far[next.first]) {
                came_from[next.first] = current.name;
                cost_so_far[next.first] = new_cost;
                frontier.emplace(graph.findNode(next.first), new_cost);
            }
        }
    }
}

std::vector<Node::NodeName> reconstruct_path(const Node::NodeName& from, const Node::NodeName& to,
                                             const std::unordered_map<Node::NodeName, Node::NodeName>& came_from) {
    std::vector<Node::NodeName> path;
    Node::NodeName current = to;
    path.push_back(current);
    while (current != from) {
        current = came_from.at(current);
        path.push_back(current);
    }
    return {path.rbegin(), path.rend()};
}

int main() {
    Graph graph;
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");
    graph.addNode("F");
    graph.addEdge("A", "B", 7);
    graph.addEdge("A", "C", 9);
    graph.addEdge("A", "F", 14);
    graph.addEdge("B", "C", 10);
    graph.addEdge("B", "D", 15);
    graph.addEdge("C", "D", 11);
    graph.addEdge("C", "F", 2);
    graph.addEdge("D", "E", 6);
    graph.addEdge("E", "F", 9);
    std::unordered_map<Node::NodeName, Node::NodeName> come_from;
    std::unordered_map<Node::NodeName, Node::EdgeWeight> cost_so_far;
    dijkstra_search(graph, "A", come_from, cost_so_far);
    std::cout << "Distance from A to E " << cost_so_far["E"] << std::endl;
    auto path = reconstruct_path("A", "E", come_from);
    std::cout << "Path from A to E" << std::endl;
    for (auto&& s : path) {
        std::cout << s;
        if (s != path.back()) {
            std::cout << " -> ";
        } else {
            std::cout << std::endl;
        }
    }
    return 0;
}