#include "Vertex.hpp"

Vertex::Vertex() : structure(Structure::None), owner(nullptr) {}

Vertex::Structure Vertex::getStructure() const {
    return structure;
}

Player* Vertex::getOwner() const {
    return owner;
}

void Vertex::buildSettlement(Player* player) {
    if (structure == Structure::None) {
        structure = Structure::Settlement;
        owner = player;
    }
}

void Vertex::upgradeToCity() {
    if (structure == Structure::Settlement) {
        structure = Structure::City;
    }
}

bool Vertex::canBuildSettlement() const {
    return structure == Structure::None;
}

const std::vector<Vertex*>& Vertex::getNeighbors() const {
    return neighbors;
}

const std::vector<Edge*>& Vertex::getEdges() const {
    return edges;
}

void Vertex::addNeighbor(Vertex* neighbor) {
    neighbors.push_back(neighbor);
}

void Vertex::addEdge(Edge* edge) {
    edges.push_back(edge);
}
