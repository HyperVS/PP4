
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <iterator>
#include <queue>
#include <limits>
#include <deque>
#include <algorithm>

class Graph : public GraphBase {
private:
        std::deque<Vertex*> vertices; // Deque that stores vertices
        std::deque<Edge*> edges; // Deque that stores edges
        unsigned long shortestDistance = 0; // Variable that stores the shortest distance after each visit
        int minimumIndex = 0; // Variable that stores the index of the vertex with the minimum distance
        std::string minimumElement = ""; // Stores the minimum element
        std::priority_queue<std::pair<unsigned long, std::string>, // Priority queue to store vertices
        std::vector<std::pair<unsigned long, std::string>>, // in ascending order
        std::greater<std::pair<unsigned long, std::string>>> paths; // by distances

protected:
        // Utility functions
        void validateLabel(std::string label); // Validate input string
        void validateLabels(std::string label1, std::string label2); // Validate input strings
        void startPath(std::string startLabel); // Start path at vertix with startLabel
        void constructPath(std::string startLabel); // Construct the path using the priority queue
        void findMinimumIndex(std::string& elem); // Find the index of the minimum vertex
        void findMinimumDistance(std::string startLabel); // Push possible paths to priority queue
        void findShortestPath(std::string endLabel, std::vector<std::string>& path); // Find the shortest path between two vertices
        void resetPath(); // Reset the path

public:
        // Constructor and Destructor
        Graph(){};
        ~Graph();

        void addVertex(std::string label); // Creates and adds a vertex to the graph with label
        void removeVertex(std::string label); // Removes the vertex with label from the graph
        void addEdge(std::string label1, std::string label2, unsigned long weight); // Adds an edge of value weight to the graph
        void removeEdge(std::string label1, std::string label2); // Removes a specific edge from the graph
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path); // Calculates the shortest path
};
#endif // GRAPH_HPP