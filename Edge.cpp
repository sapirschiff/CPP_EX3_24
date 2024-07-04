// sapirblumshtein@gmail.com

#include "Edge.hpp"
#include <iostream> // For std::cout

// Constructor with vertex indices
Edge::Edge(int v1, int v2) : vertex1(v1), vertex2(v2), owner(nullptr) {}

// Default constructor
Edge::Edge() : vertex1(0), vertex2(0), owner(nullptr) {}

// Get the owner of the edge
Player* Edge::getOwner() const {
    return owner;
}

// Build a road on the edge
void Edge::buildRoad(Player* player) {
    if (owner == nullptr) {
        owner = player;
    } else {
        std::cout << "Edge already occupied.\n";
    }
}

// Add a hexagon to the edge
void Edge::addHexagon(Hexagon* hexagon) {
    hexagons.push_back(hexagon);
}

// Get the first vertex index
int Edge::getVertex1() const {
    return vertex1;
}

// Get the second vertex index
int Edge::getVertex2() const {
    return vertex2;
}

// Get the hexagons connected to the edge
const std::vector<Hexagon*>& Edge::getHexagons() const {
    return hexagons;
}
