// Sapirblumshtein@gmail.com

#include "Vertex.hpp"
#include <iostream>  // For std::cout

Vertex::Vertex() : owner(nullptr), structure(Structure::None) {} // Constructor initializes owner and structure

Player* Vertex::getOwner() const { // Function to get the owner of the vertex
    return owner;
}

void Vertex::setOwner(Player* owner) { // Function to set the owner of the vertex
    this->owner = owner;
}

Vertex::Structure Vertex::getStructure() const { // Function to get the structure type of the vertex
    return structure;
}

void Vertex::setStructure(Structure structure) { // Function to set the structure type of the vertex
    this->structure = structure;
}

const std::vector<Edge*>& Vertex::getEdges() const { // Function to get the edges connected to the vertex
    return edges;
}

void Vertex::addEdge(Edge* edge) { // Function to add an edge to the vertex
    edges.push_back(edge);
}

const std::vector<Vertex*>& Vertex::getNeighbors() const { // Function to get the neighboring vertices
    return neighbors;
}

void Vertex::addNeighbor(Vertex* neighbor) { // Function to add a neighboring vertex
    neighbors.push_back(neighbor);
}

void Vertex::buildSettlement(Player* player) { // Function to build a settlement
    if (structure != Structure::None) {
        std::cout << "Vertex already occupied.\n";
        return;
    }
    owner = player;
    structure = Structure::Settlement;
}

void Vertex::upgradeToCity() { // Function to upgrade a settlement to a city
    if (structure != Structure::Settlement) {
        std::cout << "Vertex must have a settlement to upgrade to a city.\n";
        return;
    }
    structure = Structure::City;
}
