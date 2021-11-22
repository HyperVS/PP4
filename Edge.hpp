#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Edge {
private:
        std::string current; // The current edge
        std::string adjacent; // The adjacent edge
        unsigned long weight; // The weight associated with the edge
public:
        friend class Graph;

        // Default edge information in constructor
        Edge(std::string c = "", std::string a = "", unsigned long w = 0) {
            current = c;
            adjacent = a;
            weight = w;
        }
        ~Edge(){}
};
#endif // EDGE_HPP