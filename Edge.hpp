#ifndef EDGE_HPP
#define EDGE_HPP

#include "Player.hpp"

class Edge {
public:
    // Default constructor
    Edge();
    
    // Constructor with vertex parameters
    Edge(int v1, int v2);

    int getVertex1() const;
    int getVertex2() const;
    Player* getOwner() const;
    void setVertices(int v1, int v2);
    void buildRoad(Player* player);
    bool canBuildRoad() const;

private:
    int vertex1;
    int vertex2;
    Player* owner;
};

#endif // EDGE_HPP
