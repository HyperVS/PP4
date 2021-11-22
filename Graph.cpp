#include "Graph.hpp"

// Destructor to delete all vertices and edges
Graph::~Graph(){
    for(auto& vertex : vertices) delete vertex;
    for(auto& edge : edges) delete edge;
    vertices.clear();
    edges.clear();
}

// Validate that the label passed is not null
void Graph::validateLabel(std::string label){
    if(label.empty()) throw("Invalid input provided\n");
}

// Validate that the labels passed are not null
void Graph::validateLabels(std::string label1, std::string label2){
    if(label1.empty() || label2.empty()) throw("Invalid input provided\n");
}

// Start path at vertix with startLabel
void Graph::startPath(std::string startLabel){

        for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
            if ((*i)->vertex == startLabel) {
                    (*i)->minimumDistance = 0;
                    (*i)->shortestPath.clear();
                    (*i)->shortestPath.push_back(startLabel);
            }
        }
        paths.push(std::make_pair(0, startLabel));
}

// Traverse through the vertices deque and store the index of the minimum element
void Graph::findMinimumIndex(std::string& elem){
        int index = 0;
        for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
            if ((*i)->vertex == elem) minimumIndex = index;
            else ++index;   
        }
}

// Traverse through edges and vertices deques and push possible paths into the priority queue
void Graph::findMinimumDistance(std::string startLabel){

    // Traverse through edges deque
    for (std::deque<Edge*>::iterator e = edges.begin(); e != edges.end(); ++e){
        if ((*e)->current == minimumElement) { 

            // Traverse through vertices deque
            for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {

                // If vertex has not been visited and has an edge with a smaller weight
                if (((*e)->adjacent == (*i)->vertex) && 
                ((vertices.at(minimumIndex)->minimumDistance + (*e)->weight) < (*i)->minimumDistance) &&
                ((*i)->visited == false)){
                    
                    // Set the minimum distance
                    (*i)->minimumDistance = vertices.at(minimumIndex)->minimumDistance + (*e)->weight;

                    // Clear the path and push label
                    if (minimumElement == startLabel) {
                            (*i)->shortestPath.clear();
                            (*i)->shortestPath.push_back(startLabel);
                    }

                    // Else push a vertex at the minimum index
                    else if (minimumElement != startLabel) {
                            (*i)->shortestPath.clear();
                            (*i)->shortestPath = vertices.at(minimumIndex)->shortestPath;
                            (*i)->shortestPath.push_back(vertices.at(minimumIndex)->vertex);
                    }

                    // Make a pair of minimum distance and vertex and push to priority queue
                    paths.push(std::make_pair((*i)->minimumDistance, (*i)->vertex));
                }
            }
        }
    }
}

// Visit the two vertices from all possible paths
void Graph::constructPath(std::string startLabel){
    while(!paths.empty()){
        minimumElement = paths.top().second; // Second vertex
        paths.pop();
        findMinimumIndex(minimumElement); 
        findMinimumDistance(startLabel);
        vertices.at(minimumIndex)->visited = true;
    }
}

// Get the shortest distance and path from startLabel and endLabel
void Graph::findShortestPath(std::string endLabel, std::vector<std::string>& path){

    // Iterate through the vertices deque until vertex with endLabel is found
    for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
        if (endLabel == (*i)->vertex) { 
            
            // Store the minimum distance and path
            shortestDistance = (*i)->minimumDistance;
            (*i)->shortestPath.push_back(endLabel); 
            path = (*i)->shortestPath;
        }
    }
}

// Reset all vertices to default values
void Graph::resetPath(){

    // Iterate through vertices deque and reset to default
    for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
        (*i)->minimumDistance = std::numeric_limits<unsigned long>::max();;
        (*i)->shortestPath = {""};
        (*i)->visited = false;
    }
}

// Creates and adds a vertex to the graph with label
void Graph::addVertex(std::string label){
        validateLabel(label);
        Vertex *v = new Vertex;
        v->vertex = label;
        v->minimumDistance = std::numeric_limits<unsigned long>::max();
        v->shortestPath = {""};
        v->visited = false;
        vertices.push_back(v);
}

// Removes the vertex with label from the graph and all associated edges 
void Graph::removeVertex(std::string label){
        validateLabel(label);
    
        // Iterate through vertices deque and remove the vertex
        for (std::deque<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
            if ((*i)->vertex == label) vertices.erase(i);
        }

        // Iterate through edges deque and remove all edges associated with the removed vertex
        for (std::deque<Edge*>::iterator i = edges.begin(); i != edges.end(); ++i) {
            if (((*i)->current == label) || ((*i)->adjacent == label)) edges.erase(i);
        }
}

// Adds an edge of value weight to the graph between the vertex with label1 and the vertex with label2
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
        validateLabels(label1, label2);

        // Create edges in between label1 and label2
        Edge *e1 = new Edge(label1, label2, weight);
        Edge *e2 = new Edge(label2, label1, weight);

        // Add new edges to the end of the deque
        edges.push_back(e1);
        edges.push_back(e2);
}

// Removes the edge from the graph between the vertex with label1 and the vertex with label2
void Graph::removeEdge(std::string label1, std::string label2){
    validateLabels(label1, label2);

    // Iterate through edges deque and find the edges to be removed
    for (std::deque<Edge*>::iterator i = edges.begin(); i != edges.end(); ++i){
        if (((*i)->current == label1) && ((*i)->adjacent == label2)) edges.erase(i);
    }
}

// Calculates the shortest path between the vertex with startLabel and the vertex with endLabel using greedy Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path){
    validateLabels(startLabel, endLabel);
    
    // Select the vertex with startLabel as the starting vertex for the path
    startPath(startLabel);

    // Add vertices to priority queue in ascending order by distances
    constructPath(startLabel);

    // Traverse through the priortiy queue to find the shortest distance
    findShortestPath(endLabel, path); 

    // Reset the path
    resetPath();

    return shortestDistance;
}

