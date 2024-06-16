#include "Edge.hpp"

// Default constructor
Edge::Edge() : vertex1(-1), vertex2(-1), owner(nullptr) {}

// Constructor with vertex parameters
Edge::Edge(int v1, int v2) : vertex1(v1), vertex2(v2), owner(nullptr) {}

int Edge::getVertex1() const {
    return vertex1;
}

int Edge::getVertex2() const {
    return vertex2;
}

Player* Edge::getOwner() const {
    return owner;
}

void Edge::setVertices(int v1, int v2) {
    vertex1 = v1;
    vertex2 = v2;
}

void Edge::buildRoad(Player* player) {
    if (canBuildRoad()) {
        owner = player;
    }
}

bool Edge::canBuildRoad() const {
    return owner == nullptr;
}
