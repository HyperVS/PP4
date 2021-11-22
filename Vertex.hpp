#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

class Vertex{
private:
        std::string vertex; // A single vertex (node) in the Graph
        std::vector<std::string> shortestPath; // Vector that stores the shortest path
        unsigned long minimumDistance; // Variable that stores the minimum distance between two edges
        bool visited; // Variable to store whether the vertex in the path has been visited
public:
        friend class Graph;
        Vertex(){ vertex = ""; }
        ~Vertex(){}
};
#endif // VERTEX_HPP