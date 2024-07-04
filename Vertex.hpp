// Sapirblumshtein@gmail.com

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <stdexcept> // For std::runtime_error

class Player;  // Forward declaration

class Edge;

class Vertex {
public:
    enum class Structure { None, Settlement, City };

    Vertex();
    Player* getOwner() const; // Function to get the owner of the vertex
    Structure getStructure() const; // Function to get the structure type of the vertex
    void buildSettlement(Player* player); // Function to build a settlement
    void upgradeToCity(); // Function to upgrade a settlement to a city
    const std::vector<Edge*>& getEdges() const; // Function to get the edges connected to the vertex
    void addEdge(Edge* edge); // Function to add an edge to the vertex
    const std::vector<Vertex*>& getNeighbors() const; // Function to get the neighboring vertices
    void addNeighbor(Vertex* neighbor); // Function to add a neighboring vertex
    void setOwner(Player* player); // Function to set the owner of the vertex
    void setStructure(Structure structure); // Function to set the structure type of the vertex

private:
    Player* owner; // Pointer to the player who owns the vertex
    Structure structure; // Type of structure (None, Settlement, City)
    std::vector<Edge*> edges; // List of edges connected to the vertex
    std::vector<Vertex*> neighbors; // List of neighboring vertices
};

#endif // VERTEX_HPP
