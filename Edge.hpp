// sapirblumshtein@gmail.com

#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>
#include "Player.hpp"
#include "Hexagon.hpp"

class Player; // Forward declaration
class Hexagon; // Forward declaration

class Edge {
private:
    int vertex1; // Index of the first vertex
    int vertex2; // Index of the second vertex
    Player* owner; // Owner of the edge
    std::vector<Hexagon*> hexagons; // Hexagons connected to the edge

public:
    Edge(); // Default constructor
    Edge(int v1, int v2); // Constructor with vertex indices
    Player* getOwner() const; // Get the owner of the edge
    void buildRoad(Player* player); // Build a road on the edge
    void addHexagon(Hexagon* hexagon); // Add a hexagon to the edge
    int getVertex1() const; // Get the first vertex index
    int getVertex2() const; // Get the second vertex index
    const std::vector<Hexagon*>& getHexagons() const; // Get the hexagons connected to the edge
};

#endif // EDGE_HPP
