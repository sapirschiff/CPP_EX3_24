#include "Hexagon.hpp"

Hexagon::Hexagon(const std::string& resource, int number)
    : resource(resource), number(number) {}

std::string Hexagon::getResource() const {
    return resource;
}

int Hexagon::getNumber() const {
    return number;
}

void Hexagon::addVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

void Hexagon::addEdge(Edge* edge) {
    edges.push_back(edge);
}

const std::vector<Vertex*>& Hexagon::getVertices() const {
    return vertices;
}

const std::vector<Edge*>& Hexagon::getEdges() const {
    return edges;
}
