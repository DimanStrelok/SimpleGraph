#pragma once

#include <iostream>
#include <map>
#include <string>
#include <tuple>

struct Node {
    std::string name;
    std::map<std::string, double> edges;

    Node() = default;

    Node(const std::string& name_);

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

    friend std::istream& operator>>(std::istream& is, Node& node);

    bool operator<(const Node& rhs) const;

    bool operator>(const Node& rhs) const;

    bool operator<=(const Node& rhs) const;

    bool operator>=(const Node& rhs) const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    void addEdge(const std::string& to, double weight);

    void updateEdge(const std::string& to, double weight);

    void removeEdge(const std::string& to);
};