// sapirblumshtein@gmail.com

#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <vector>
#include <string> // For std::string
#include "Resource.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Vertex; // Forward declaration

class Hexagon {
private:
    Resource resource; // Resource type of the hexagon
    int number; // Number associated with the hexagon
    std::vector<Vertex*> vertices; // Vertices surrounding the hexagon
    std::vector<Edge*> edges; // Edges surrounding the hexagon

public:
    Hexagon(Resource resource, int number); // Constructor
    Resource getResource() const; // Get the resource type of the hexagon
    std::string getResourceType() const; // Get the resource type as a string
    static std::string resourceToString(Resource resource); // Convert resource enum to string
    int getNumber() const; // Get the number of the hexagon
    void addVertex(Vertex* vertex); // Add a vertex to the hexagon
    void addEdge(Edge* edge); // Add an edge to the hexagon
    const std::vector<Vertex*>& getVertices() const; // Get the vertices of the hexagon
    const std::vector<Edge*>& getEdges() const; // Get the edges of the hexagon
};

#endif // HEXAGON_HPP
