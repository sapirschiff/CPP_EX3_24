#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Player.hpp"
#include <vector>

class Edge;  // Forward declaration

class Vertex {
public:
    enum class Structure { None, Settlement, City };

    Vertex();

    Structure getStructure() const;
    Player* getOwner() const;
    void buildSettlement(Player* player);
    void upgradeToCity();
    bool canBuildSettlement() const;

    // methods to handle neighbors and edges
    const std::vector<Vertex*>& getNeighbors() const;
    const std::vector<Edge*>& getEdges() const;
    void addNeighbor(Vertex* neighbor);
    void addEdge(Edge* edge);

private:
    Structure structure;
    Player* owner;
    std::vector<Vertex*> neighbors;  // Adjacent vertices
    std::vector<Edge*> edges;        // Adjacent edges
};

#endif // VERTEX_HPP
