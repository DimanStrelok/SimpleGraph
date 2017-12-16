#include <iostream>
#include <queue>
#include <map>
#include <random>

#include "Graph.h"

void dijkstra_search(const Graph& graph, const std::string& start,
                     std::map<std::string, std::string>& came_from, std::map<std::string, double>& cost_so_far) {
    std::priority_queue<std::pair<Node, double>, std::vector<std::pair<Node, double>>, std::greater<>> frontier;
    frontier.emplace(graph.findNode(start), 0);
    came_from[start] = start;
    cost_so_far[start] = 0;
    Node current;
    double dist;
    while (!frontier.empty()) {
        std::tie(current, dist) = frontier.top();
        frontier.pop();
        if (dist > cost_so_far[current.name]) {
            continue;
        }
        for (auto&& next : current.edges) {
            double new_cost = cost_so_far[current.name] + next.second;
            if (cost_so_far.count(next.first) == 0 || new_cost < cost_so_far[next.first]) {
                came_from[next.first] = current.name;
                cost_so_far[next.first] = new_cost;
                frontier.emplace(graph.findNode(next.first), new_cost);
            }
        }
    }
}

std::vector<std::string> reconstruct_path(const std::string& from, const std::string& to,
                                          const std::map<std::string, std::string>& came_from) {
    std::vector<std::string> path = {to};
    std::string current = to;
    while (current != from) {
        current = came_from.at(current);
        path.push_back(current);
    }
    return {path.rbegin(), path.rend()};
}

void printPath(const std::vector<std::string>& path) {
    for (auto&& s : path) {
        std::cout << s;
        if (s != path.back()) {
            std::cout << " -> ";
        } else {
            std::cout << std::endl;
        }
    }
}

void printAllCosts(const std::string& from, const Graph& graph, const std::map<std::string, double>& cost_so_far) {
    for (auto&& e : graph.getNodes()) {
        std::cout << "Distance from " << from << " to " << e.name << " = " << cost_so_far.at(e.name) << std::endl;
    }
}

void printAllPaths(const std::string& from, const Graph& graph, const std::map<std::string, std::string>& come_from) {
    for (auto&& e : graph.getNodes()) {
        auto path = reconstruct_path(from, e.name, come_from);
        std::cout << "Path from " << from << " to " << e.name << std::endl;
        printPath(path);
    }
}

int main() {
    Graph graph;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(1, 999);
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addEdge("A", "B", dis(gen));
    graph.addEdge("A", "C", dis(gen));
    graph.addEdge("B", "C", dis(gen));
    std::map<std::string, std::string> come_from;
    std::map<std::string, double> cost_so_far;
    dijkstra_search(graph, "A", come_from, cost_so_far);
    printAllCosts("A", graph, cost_so_far);
    printAllPaths("A", graph, come_from);
    std::cout << graph << std::endl;
    return 0;
}