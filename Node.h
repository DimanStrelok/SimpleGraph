#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>

struct Node {

    using NodeName = std::string;

    using EdgeWeight = int;

    NodeName name;
    std::unordered_map<NodeName, EdgeWeight> edges;

    Node() = default;

    Node(const NodeName& name_);

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

    friend std::istream& operator>>(std::istream& is, Node& node);

    bool operator<(const Node& rhs) const;

    bool operator>(const Node& rhs) const;

    bool operator<=(const Node& rhs) const;

    bool operator>=(const Node& rhs) const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    void addEdge(const NodeName& to, EdgeWeight weight);

    void updateEdge(const NodeName& to, EdgeWeight weight);

    void removeEdge(const NodeName& to);
};

namespace std {
    template<>
    struct hash<Node> {
        using argument_type = Node;
        using result_type = std::size_t;

        result_type operator()(const argument_type& s) const noexcept {
            return std::hash<std::string>()(s.name);
        }
    };
}  // namespace std