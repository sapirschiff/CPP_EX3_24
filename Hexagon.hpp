#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"

class Hexagon {
private:
    std::string resource;
    int number;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

public:
    Hexagon(const std::string& resource, int number);
    std::string getResource() const;
    int getNumber() const;
    void addVertex(Vertex* vertex);
    void addEdge(Edge* edge);
    const std::vector<Vertex*>& getVertices() const;
    const std::vector<Edge*>& getEdges() const;
};

#endif // HEXAGON_HPP
