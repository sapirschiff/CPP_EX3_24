// sapirblumshtein@gmail.com

#include "Hexagon.hpp"

// Constructor to initialize resource and number
Hexagon::Hexagon(Resource resource, int number) : resource(resource), number(number) {}

// Get the resource type as a string
std::string Hexagon::getResourceType() const {
    switch (resource) {
        case WOOD:
            return "WOOD";
        case BRICK:
            return "BRICK";
        case SHEEP:
            return "SHEEP";
        case WHEAT:
            return "WHEAT";
        case CLAY:
            return "IRON";
        case DESERT:
            return "DESERT";
        default:
            return "UNKNOWN";
    }
}

// Convert resource enum to string
std::string Hexagon::resourceToString(Resource resource) {
    switch (resource) {
        case WOOD: return "WOOD";
        case BRICK: return "BRICK";
        case SHEEP: return "SHEEP";
        case WHEAT: return "WHEAT";
        case CLAY: return "CLAY";
        case DESERT: return "DESERT";
        default: return "UNKNOWN";
    }
}

// Get the number of the hexagon
int Hexagon::getNumber() const {
    return number;
}

// Get the resource type of the hexagon
Resource Hexagon::getResource() const {
    return resource;
}

// Add a vertex to the hexagon
void Hexagon::addVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

// Add an edge to the hexagon
void Hexagon::addEdge(Edge* edge) {
    edges.push_back(edge);
}

// Get the vertices of the hexagon
const std::vector<Vertex*>& Hexagon::getVertices() const {
    return vertices;
}

// Get the edges of the hexagon
const std::vector<Edge*>& Hexagon::getEdges() const {
    return edges;
}
